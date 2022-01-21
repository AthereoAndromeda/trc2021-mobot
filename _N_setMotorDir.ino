
void setMotorDir(Direction _cmd)
{
  switch (_cmd)
  {
    case Forward:
      PORTA = 0xAA;
      break;
    case Backward:
      PORTA = 0x55;
      break;
    case Left:
      PORTA = 0x99;
      break;
    case Right:
      PORTA = 0x66;
      break;
    case Forward_Left:
      PORTA = 0x88;
      break;
    case Forward_Right:
      PORTA = 0x22;
      break;
    case Backward_Left:
      PORTA = 0x44;
      break;
    case Backward_Right:
      PORTA = 0x11;
      break;
    case CW_Center_Center:
      PORTA = 0x69;
      break;
    case CCW_Center_Center:
      PORTA = 0x96;
      break;
    case CW_Back_Center:
      PORTA = 0x5F;
      break;
    case CCW_Back_Center:
      PORTA = 0xAF;
      break;
    case CW_Front_Center:
      PORTA = 0xF5;
      break;
    case CCW_Front_Center:
      PORTA = 0xFA;
      break;
    case CW_Center_Left:
      PORTA = 0x7D;
      break;
    case CCW_Center_Left:
      PORTA = 0xBE;
      break;
    case CW_Center_Right:
      PORTA = 0xEB;
      break;
    case CCW_Center_Right:
      PORTA = 0xD7;
      break;

    case Stop:
      PORTA = 0xFF;
      break;

    default:
      Serial.println("Unknown Direction!");
      while (true);
      break;
  }
}
