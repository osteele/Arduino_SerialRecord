class SerialRecord {
 public:
  const int size;
  int *values;

  SerialRecord(int count = 1)
      : size(count), values(new int[count]), m_buffer(new int[count]) {}

  const int &get(int index = 0) {
    if (0 <= index && index < size) {
      return values[index];
    } else {
      Serial.println("Error: SerialValueReader.get index out of bounds");
      return -1;
    }
  }

  int set(int index, int value) {
    if (0 <= index && index < size) {
      values[index] = value;
    } else {
      Serial.println("Error: SerialValueReader.set index out of bounds");
    }
  }

  int set(int value) { set(0, value); }

  const int &operator[](int index) { return get(index); }

  // receive serial data
  void read() {
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\n') {
        firstLine = false;
        switch (m_readState) {
          case IN_FIELD:
            m_buffer[m_ix++] = m_accum;
          // fall through
          case FIELD_START:
            if (m_ix < size) {
              Serial.print(
                  "Error: SerialValueReader received too few values: ");
              Serial.print(m_ix);
              Serial.print("expected ");
              Serial.println(size);
            }
            // Go ahead and copy the buffered values to the values array, even
            // if there is the wrong number of them. This is more convenient for
            // incremental development.
            memcpy(values, m_buffer, size * sizeof values[0]);
            break;
        }
        m_readState = LINE_START;
      } else {
        switch (m_readState) {
          case LINE_START:
            if (c == ' ' || c == '\t') break;
            if (c == '!') {  // commands
              m_readState = COMMAND;
              break;
            }
            m_readState = FIELD_START;
            m_ix = 0;
            // fall through
          case FIELD_START:
            if (m_ix >= size) {
              Serial.println(
                  "Error: SerialValueReader received too many values");
              m_readState = SKIP_LINE;
              break;
            }
            m_readState = IN_FIELD;
            m_accum = 0;
            // fall through
          case IN_FIELD:
            switch (c) {
              case '0' ... '9':
                m_accum *= 10;
                m_accum += c - '0';
                // TODO: warn on overflow
                break;
              case ' ':
              case '\t':
              case ',':  // end of field
                m_buffer[m_ix++] = m_accum;
                m_readState = FIELD_START;
                break;
              default:
                reportInvalidCharacter(
                    "Error: SerialValueReader received invalid character: ", c);
                m_readState = SKIP_LINE;
                break;
            }
            break;
          case COMMAND:
            switch (c) {
              case 'e':
                send();
                m_readState = SKIP_LINE;
                break;
              case ' ':
              case '\t':
                break;
              default:
                reportInvalidCharacter(
                    "Error: SerialValueReader received unknown command: ", c);
                m_readState = SKIP_LINE;
            }
            break;
        }
      }
    }
  }

  void reportInvalidCharacter(char *message, char c) {
    if (firstLine) return;

    Serial.print(message);
    Serial.print('\'');
    Serial.print(c);
    Serial.print("' (");
    Serial.print(static_cast<unsigned char>(c));
    Serial.println(")");
  }

  void send() {
    for (int i = 0; i < size; i++) {
      if (i > 0) {
        Serial.print(',');
      }
      Serial.print(values[i]);
    }
    Serial.println();
  }

  void send(int value) {
    set(value);
    send();
  }

 private:
  int m_ix = 0;
  int m_accum = 0;
  bool firstLine = true;
  int *m_buffer;

  enum ReadState {
    LINE_START,
    FIELD_START,
    IN_FIELD,
    COMMAND,
    SKIP_LINE,
  };
  ReadState m_readState = LINE_START;
};
