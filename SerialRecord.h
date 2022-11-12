/* SerialRecord — an Arduino library for sending and receiving data over a
 * serial connection. Created by Oliver Steele, 2020-2022. Available under the
 * GNU LGPL license.
 */

#ifndef SerialRecord_h
#define SerialRecord_h

class SerialRecord {
 public:
  const int size;
  int *values;

  SerialRecord(int count = 1)
      : size(count),
        values(new int[count]),
        m_buffer(new int[count]),
        m_fieldNames(new String[size]) {}

  /** Returns the value at the given index. */
  int &get(int index = 0) {
    static int sentinel;
    if (0 <= index && index < size) {
      return values[index];
    } else {
      Serial.println("Error: SerialValueReader index out of bounds (" +
                     String(index) +
                     (index < 0 ? " < 0)" : +" >= " + String(size) + ")"));
      sentinel = -1;
      return sentinel;
    }
  }

  /** Sets the value at the given index. */
  void set(int index, int value) {
    if (0 <= index && index < size) {
      values[index] = value;
    } else {
      Serial.println("Error: SerialValueReader.set index out of bounds");
    }
  }

  /** Sets the first value. */
  void set(int value) {
    set(0, value);
  }

  /** References the value at the given index. */
  int &operator[](int index) {
    return get(index);
  }

  void setFieldName(int index, String name) {
    if (0 <= index && index < size) {
      m_fieldNames[index] = name;
    } else {
      Serial.println(
          "Error: SerialValueReader.setFieldName index out of bounds");
    }
  }

  /** Receive serial data. Returns true if a new record was received. */
  bool read() {
    bool recordIsComplete = false;
    while (Serial.available() && !recordIsComplete) {
      char c = Serial.read();
      if (c == '\n') {
        firstLine = false;
        switch (m_readState) {
          case IN_FIELD:
            m_buffer[m_ix++] = m_accum;
          // fall through
          case FIELD_START:
            if (m_ix < size) {
              Serial.println(
                  "Error: SerialValueReader received too few values: " +
                  String(m_ix) + " < " + String(size));
            }
            // Go ahead and copy the buffered values to the values array, even
            // if there is the wrong number of them. This is more convenient for
            // incremental development.
            memcpy(values, m_buffer, size * sizeof values[0]);
            recordIsComplete = true;
            break;
          case COMMAND:
          case LINE_START:
          case SKIP_LINE:
            break;
        }
        m_readState = LINE_START;
      } else {
        switch (m_readState) {
          case LINE_START:
            // This clause handles characters that are meaningful only at the
            // beginning of a line. It then falls through to FIELD_START (the
            // beginning of a line is also the beginning of a field), to handle
            // characters that don't have a special line-initial meaning.
            if (c == ' ' || c == '\t')
              break;         // ignore whitespace at the beginning of a line
            if (c == '!') {  // Command prefix character. The next character is
                             // a command.
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
            m_accum = 0;  // initialize the field value accumulator
            // fall through
          case IN_FIELD:
            switch (c) {
              case '0' ... '9':
                m_accum *= 10;
                m_accum += c - '0';
                // TODO: warn on overflow
                break;
              case ' ':  // space, tab, semicolon, and comma separate (and
                         // therefore terminate) fields
              case '\t':
              case ';':
              case ',':
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
            // This clause handles characters that follow a '!' command prefix.
            // (There is currently only one such command, "!e".)
            switch (c) {
              case 'e':
                // Echo. Transmit back the last received values received on this
                // SerialRecord, for debugging.
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
          case SKIP_LINE:
            break;
        }
      }
    }
    return recordIsComplete;
  }

  /** Send data to the serial port. */
  void send() {
    for (int i = 0; i < size; i++) {
      if (i > 0) {
        Serial.print(',');
      }
      if (m_fieldNames[i].length() > 0) {
        Serial.print(m_fieldNames[i]);
        Serial.print(':');
      }
      Serial.print(values[i]);
    }
    Serial.println();
  }

  /** Send data to the serial port. This method is a synonym for send.*/
  void send(int value) {
    set(value);
    send();
  }

  /** Send data to the serial port. This method is a synonym for send.*/
  void write() {
    send();
  }

 private:
  int m_ix = 0;
  int m_accum = 0;
  bool firstLine = true;
  int *m_buffer;
  String *m_fieldNames;

  enum ReadState {
    LINE_START,
    FIELD_START,
    IN_FIELD,
    COMMAND,
    SKIP_LINE,
  };
  ReadState m_readState = LINE_START;

  void reportInvalidCharacter(const char *message, int c) {
    if (firstLine) return;

    Serial.print(message);
    Serial.print('\'');
    Serial.print(c);
    Serial.print("' (");
    Serial.print(static_cast<unsigned char>(c));
    Serial.println(")");
  }
};

#endif  // SerialRecord_h
