class SerialValueReader
{
public:
  SerialValueReader(int count = 1) : size(count), values(new int[count]), m_buffer(new int[count]) {}
  const int size;
  int *values;

  const int get(int index)
  {
    if (0 <= index && index < size)
    {
      return values[index];
    }
    else
    {
      Serial.println("Error: SerialValueReader.get index out of bounds");
      return -1;
    }
  }

  int set(int index, int value)
  {
    if (0 <= index && index < size)
    {
      values[index] = value;
    }
    else
    {
      Serial.println("Error: SerialValueReader.set index out of bounds");
    }
  }

  const int operator[](int index)
  {
    return get(index);
  }

  // int operator[] =(int index, int value)
  // {
  //   return get(index);
  // }

  // int value()
  // {
  //   return this->get(0);
  // }

  // receive serial data from Processing
  void getSerialData()
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (c == '\n')
      {
        switch (m_readState)
        {
        case IN_FIELD:
          values[m_ix++] = m_accum;
          if (m_ix < size)
          {
            Serial.println("Error: SerialValueReader received too few values");
          }
          break;
        }
        m_readState = LINE_START;
      }
      else
      {
        switch (m_readState)
        {
        case LINE_START:
          if (c == '!') // commands
          {
            m_readState = COMMAND;
            break;
          }
          m_readState = FIELD_START;
          m_ix = 0;
          // fall through to start field
        case FIELD_START:
          if (m_ix > size)
          {
            Serial.println("Error: SerialValueReader received too many values");
            break;
          }
          m_accum = 0;
          // fall through to in field
        case IN_FIELD:
          switch (c)
          {
          case '0' ... '9':
            m_accum *= 10;
            m_accum += c - '0';
            // TODO: warn on overflow
            break;
          case ' ':
          case ',': // end of field
            values[m_ix++] = m_accum;
            m_readState = FIELD_START;
            break;
          default:
            reportInvalidCharacter("Error: SerialValueReader received invalid character: ", c);
            m_readState = SKIP_LINE;
            break;
          }
          break;
        case COMMAND:
          switch (c)
          {
          case 'e':
            send();
            break;
          default:
            reportInvalidCharacter("Error: SerialValueReader received unknown command: ", c);
          }
          m_readState = SKIP_LINE;
          break;
        }
      }
    }
  }
  void reportInvalidCharacter(char *message, char c)
  {
    Serial.print(message);
    Serial.print(c);
    Serial.print(" (");
    Serial.print(static_cast<unsigned char>(c));
    Serial.println(")");
  }

  void
  send()
  {
    for (int i = 0; i < size; i++)
    {
      if (i > 0)
      {
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

  enum ReadState
  {
    LINE_START,
    // RECORD,
    FIELD_START,
    IN_FIELD,
    COMMAND,
    SKIP_LINE,
  };
  ReadState m_readState = LINE_START;
};
