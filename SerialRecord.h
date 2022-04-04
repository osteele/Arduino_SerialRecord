class SerialValueReader {
 public:
  const int size;
  int *values;

  SerialValueReader(int count = 1)
      : size(count), values(new int[count]), m_buffer(new int[count]) {}

  const int get(int index) {
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

  const int operator[](int index) { return get(index); }

  // receive serial data from Processing
  void getSerialData() {
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\n') {
        switch (m_readState) {
          case IN_FIELD:
            values[m_ix++] = m_accum;
          // fall through
          case FIELD_START:
            if (m_ix < size) {
              Serial.print(
                  "Error: SerialValueReader received too few values: ");
              Serial.print(m_ix);
              Serial.print(" instead of ");
              Serial.println(size);
            }
            break;
        }
        m_readState = LINE_START;
      } else {
        switch (m_readState) {
          case LINE_START:
            if (c == '!')  // commands
            {
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
              case ',':  // end of field
                values[m_ix++] = m_accum;
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
                break;
              default:
                reportInvalidCharacter(
                    "Error: SerialValueReader received unknown command: ", c);
            }
            m_readState = SKIP_LINE;
            break;
        }
      }
    }
  }
  void reportInvalidCharacter(char *message, char c) {
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

 private:
  int m_ix = 0;
  int m_accum = 0;
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
