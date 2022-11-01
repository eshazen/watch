int Epd::HDirInit(void)
{
  /* this calls the peripheral hardware interface, see epdif */
  if (IfInit() != 0) {
    return -1;
  }
  /* EPD hardware init start */
  Reset();

  WaitUntilIdle();
  SendCommand(0x12);  //SWRESET
  WaitUntilIdle();

  SendCommand(0x01); //Driver output control
  SendData(0xC7);
  SendData(0x00);
  SendData(0x01);    // 01-high 00-low (TB bit X scan direction)

  SendCommand(0x11); //data entry mode
  SendData(0x01);    // 01-high 03-low

  SendCommand(0x44); //set Ram-X address start/end position

  SendData(0x00);
  SendData(0x18);    //0x0C-->(18+1)*8=200

  SendCommand(0x45); //set Ram-Y address start/end position

  SendData(0xC7);   // c7-high  00-low
  SendData(0x00);   
  SendData(0x00);   // 00-high  18-low
  SendData(0x00);   //

  SendCommand(0x3C); //BorderWavefrom
  SendData(0x01);

  SendCommand(0x18);
  SendData(0x80);

  SendCommand(0x22); // //Load Temperature and waveform setting.
  SendData(0XB1);
  SendCommand(0x20);

  SendCommand(0x4E);   // set RAM x address count to 0;
  SendData(0x00);
  SendCommand(0x4F);   // set RAM y address count to 0X199;
  SendData(0xC7);
  SendData(0x00);
  WaitUntilIdle();

  SetLut(WF_Full_1IN54);
  /* EPD hardware init end */

  return 0;
}
