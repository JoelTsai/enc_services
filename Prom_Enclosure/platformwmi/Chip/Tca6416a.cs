/*---------------------------------------------------------------------------**
**          Filename    : Tca6416a.cs                                        **
**          Description :Contorl Tca6416a chip                               **
**          Created on  :2019/07/15                                          **
**          Created by  : Cheng-Chieh Lai                                    **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;




namespace Chip.Contrl
{
    static class TCA6416_Constants
    {
        public const uint BLEN = 1;
        public const uint WLEN = 2;
        public const uint DWLEN = 4;

        public const uint ENC_LED_OFF = 0x00;
        public const uint ENC_LED_GREEN = 0x01;
        public const uint ENC_LED_RED = 0x02;
        public const uint ENC_LED_AMBER = 0x03;
        public const uint ENC_LED_DARK = 0x80;

        public const uint TCA6416A_I2C_ADDR_LO = 0x20;
		public const uint TCA6416A_I2C_ADDR_HI = 0x21;

		public const uint TCA6416A_PORT_0 	= 0;
		public const uint TCA6416A_PORT_1 	= 1;

        public const uint TCA6416A_INPUT_PORT_0 = 0x0;
        public const uint TCA6416A_INPUT_PORT_1 = 0x1;
        public const uint TCA6416A_OUTPUT_PORT_0 =0x2;
        public const uint TCA6416A_OUTPUT_PORT_1 =0x3;
        public const uint TCA6416A_POLARITY_PORT_0 = 0x4;
        public const uint TCA6416A_POLARITY_PORT_1 = 0x5;
        public const uint TCA6416A_CONFIG_PORT_0 = 0x6;
        public const uint TCA6416A_CONFIG_PORT_1 = 0x7;

        public const uint TCA6416A_GPIO_IN 	= 1;
		public const uint TCA6416A_GPIO_OUT = 0;

        public const uint TCA6416A_GPIO_PIN_0 = 0;
        public const uint TCA6416A_GPIO_PIN_1 = 1;
        public const uint TCA6416A_GPIO_PIN_2 = 2;
        public const uint TCA6416A_GPIO_PIN_3 = 3;
        public const uint TCA6416A_GPIO_PIN_4 = 4;
        public const uint TCA6416A_GPIO_PIN_5 = 5;
        public const uint TCA6416A_GPIO_PIN_6 = 6;
        public const uint TCA6416A_GPIO_PIN_7 = 7;
        public const uint TCA6416A_GPIO_PIN_8 = 8;
        public const uint TCA6416A_GPIO_PIN_9 = 9;
        public const uint TCA6416A_GPIO_PIN_10 = 10;
        public const uint TCA6416A_GPIO_PIN_11 = 11;
        public const uint TCA6416A_GPIO_PIN_12 = 12;
        public const uint TCA6416A_GPIO_PIN_13 = 13;
        public const uint TCA6416A_GPIO_PIN_14 = 14;
        public const uint TCA6416A_GPIO_PIN_15 = 15;

        public const uint ENC_LED_HDD_0         = 0;
		public const uint ENC_LED_HDD_1         = 1;
		public const uint ENC_LED_HDD_2         = 2;
		public const uint ENC_LED_HDD_3         = 3;
		public const uint ENC_LED_HDD_4         = 4;
		public const uint ENC_LED_HDD_5         = 5;
		public const uint ENC_LED_HDD_6         = 6;
		public const uint ENC_LED_HDD_7         = 7;
		public const uint ENC_LED_HDD_8         = 8;
		public const uint ENC_LED_HDD_9         = 9;
		public const uint ENC_LED_HDD_10        = 10;
		public const uint ENC_LED_HDD_11        = 11;
		public const uint ENC_LED_HDD_12        = 12;
		public const uint ENC_LED_HDD_13        = 13;
		public const uint ENC_LED_HDD_14        = 14;
		public const uint ENC_LED_HDD_15        = 15;
		public const uint ENC_LED_HDD           = 16;
		public const uint ENC_LED_POWER         = 17;
		public const uint ENC_LED_OPAS          = 18;
		public const uint ENC_LED_GLOBE_ERR     = 19;
		public const uint ENC_LED_RAID          = 20;
		public const uint ENC_LED_RECORD        = 21;
		public const uint ENC_LED_FAN           = 22;
		public const uint ENC_LED_BATTERY       = 23;
		public const uint ENC_LED_DEBUG         = 24;
		public const uint ENC_LED_PSU           = 25;
		public const uint ENC_LED_ETH1          = 26;
		public const uint ENC_LED_ETH2          = 27;

		public static ushort[] LedRegisters = new ushort[] { 0x20 ,0x21 };
        public const uint FW_REQUEST_PORT0_MASK = 0x30;
        public const uint FW_REQUEST_PORT1_MASK = 0x00;
        public const uint NET_REQUEST_MASK = 0x3C;
        public const uint OPAS_REQUEST_MASK = 0x03;

    }//end of Constants
	
	public class TCA6416
	{
        private const uint TCA6416A_GPIO_MAX = 15;
        //public PCHSMBUS SMB;
        public TCA6416()
		{
            //this.SMB = new PCHSMBUS();
            uint data_temp = 0x00;
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_LO, TCA6416_Constants.TCA6416A_OUTPUT_PORT_0, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_LO, TCA6416_Constants.TCA6416A_OUTPUT_PORT_1, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_OUTPUT_PORT_0, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_OUTPUT_PORT_1, ref data_temp);

            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_LO, TCA6416_Constants.TCA6416A_CONFIG_PORT_0, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_LO, TCA6416_Constants.TCA6416A_CONFIG_PORT_1, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_CONFIG_PORT_0, ref data_temp);

            data_temp = 0x80;
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_CONFIG_PORT_1, ref data_temp);

            data_temp = 0x00;
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_LO, TCA6416_Constants.TCA6416A_OUTPUT_PORT_0, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_LO, TCA6416_Constants.TCA6416A_OUTPUT_PORT_1, ref data_temp);
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_OUTPUT_PORT_1, ref data_temp);

            data_temp = 0x44;
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_OUTPUT_PORT_0, ref data_temp);
            data_temp = 0x1;
            Tca6416a_write_value(TCA6416_Constants.TCA6416A_I2C_ADDR_HI, TCA6416_Constants.TCA6416A_OUTPUT_PORT_1, ref data_temp);
        }

		public int Tca6416a_write_value(uint addr, uint reg, ref uint data)
		{
			// return pch200_smbus_write(addr, reg, PCH_BYTE_DATA, data, BLEN);
			uint[] data_temp = { data };
			return PCHSMBUS.WriteSMB(addr, reg, TCA6416_Constants.BLEN, ref data_temp);
		}

		public int Tca6416a_read_value(uint addr, uint reg, ref uint data)
		{

			//return pch200_smbus_read(addr, reg, PCH_BYTE_DATA, data, BLEN);
			int ret;
			uint[] data_temp = { data };
			ret = PCHSMBUS.ReadSMB(addr, reg, TCA6416_Constants.BLEN, ref data_temp);
			data = data_temp[0];
			return ret;

		}

		/*
		public void Tca6416a_get_led()
		{
			uint offset = 0;
			uint data, ldata, hdata;
			uint addr;
			uint fanCount;
		}
		*/	
		public void tca6416a_set_gpio_port_value (uint addr, uint port, ref uint data)
		{
			uint reg = 0;
			
			if (port == TCA6416_Constants.TCA6416A_PORT_0)
			{
				reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_0;
			}
			else if (port == TCA6416_Constants.TCA6416A_PORT_1)
			{
				reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_1;
			}
		
			Tca6416a_write_value (addr, reg,ref data);
		}

        public void tca6416a_get_gpio_port_value (uint addr, uint port, ref uint data)
        {
            uint reg = 0;

            if (port == TCA6416_Constants.TCA6416A_PORT_0)
            {
                reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_0;
            }
            else if (port == TCA6416_Constants.TCA6416A_PORT_1)
            {
                reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_1;
            }

            Tca6416a_read_value(addr, reg,ref data);
        }

		public void encSetLedStatus(uint chipId, uint port, uint PinId)
		{
			uint addr=0;
            switch(chipId)
			{
				case 0:
					addr=TCA6416_Constants.TCA6416A_I2C_ADDR_LO;
					break;
				case 1:
					addr=TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
                    if (port == TCA6416_Constants.TCA6416A_PORT_0)
                    {
                       uint gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_2;
                       uint gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_3;
                       uint temp = 1;

                        PinId &= TCA6416_Constants.FW_REQUEST_PORT0_MASK;
                        switch (Enclsoure.Enclsoure_class.Fan_color)
                        {
                            case TCA6416_Constants.ENC_LED_GREEN:
                                PinId |= temp << Convert.ToInt32(gpio_G);
                                PinId &= ~(temp << Convert.ToInt32(gpio_R));
                                break;

                            case TCA6416_Constants.ENC_LED_RED:
                                PinId &= ~(temp << Convert.ToInt32(gpio_G));
                                PinId |= temp << Convert.ToInt32(gpio_R);
                                break;

                            case TCA6416_Constants.ENC_LED_AMBER:
                                PinId |= temp << Convert.ToInt32(gpio_G);
                                PinId |= temp << Convert.ToInt32(gpio_R);
                                break;

                            case TCA6416_Constants.ENC_LED_OFF:
                            case TCA6416_Constants.ENC_LED_DARK:
                                PinId &= ~(temp << Convert.ToInt32(gpio_G));
                                PinId &= ~(temp << Convert.ToInt32(gpio_R));
                                break;

                            default:
                                //ENC_DBG_PRINT("Led get error status %d\n", status);
                                break;
                        }
                        if ((PinId & TCA6416_Constants.FW_REQUEST_PORT0_MASK) == 0x20)
                        { Enclsoure.Enclsoure_class.GlobeError_LED_trigger = true; }
                        else
                        { Enclsoure.Enclsoure_class.GlobeError_LED_trigger = false; }

                        PinId |= 0x40;//POWER LED Enable
                        PinId |= Enclsoure.Enclsoure_class.OPAS_LED;


                    }
                    if (port == TCA6416_Constants.TCA6416A_PORT_1)
                    {
                        PinId &= TCA6416_Constants.FW_REQUEST_PORT1_MASK;
                        uint gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_0;
                        uint gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_1;
                        uint temp = 1;

                        if (Enclsoure.Enclsoure_class.Fan_color== TCA6416_Constants.ENC_LED_RED||
                           Enclsoure.Enclsoure_class.GlobeError_LED_trigger)
                        {
                            PinId &= ~(temp << Convert.ToInt32(gpio_G));
                            PinId |= temp << Convert.ToInt32(gpio_R);
                        }
                        else
                        {
                            PinId |= temp << Convert.ToInt32(gpio_G);
                            PinId &= ~(temp << Convert.ToInt32(gpio_R));
                        }
                        PinId |= Enclsoure.Enclsoure_class.NET_LED;
                    }

                    break;
			}
			tca6416a_set_gpio_port_value (addr, port, ref PinId);
			
			Console.WriteLine("encSetLedStatus End!");
		}

		public void encGetLedStatus(ref uint?[] Ledreg)
		{
			uint chipId=0;
			uint data_port_0=0;
			uint data_port_1=0;
			uint date_reg=0;
            uint PinId = 0;

            for (int i=0; i<TCA6416_Constants.LedRegisters.Length;i++)
			{
                chipId =TCA6416_Constants.LedRegisters[i];
				tca6416a_get_gpio_port_value (chipId, TCA6416_Constants.TCA6416A_PORT_0, ref PinId);
				data_port_0=PinId;
				tca6416a_get_gpio_port_value (chipId, TCA6416_Constants.TCA6416A_PORT_1, ref PinId);
				data_port_1=PinId;
				date_reg=(uint) (data_port_0 | (data_port_1<< 16));
				Ledreg[i] = date_reg;
				/*
				Console.WriteLine("chipId=[{0:x}]", chipId);
				Console.WriteLine("i=[{0:x}]", i);
				Console.WriteLine("PinId  =[{0:x}]", PinId);*/
				//Console.WriteLine("date_reg[{0}]=[{1:x}]", i,date_reg);
				
			}
			/*
			for (int i=0; i<TCA6416_Constants.LedRegisters.Length;i++)
			{
				Console.WriteLine("Ledreg  =[{0:x}]", Ledreg[i]);
			}
			*/
			//Console.WriteLine("encGetLedStatus End!");
		}
        public void NCT6414_FAN_Control(uint LEDID, uint status)
        {
            uint bitmap = 0;
            uint addr = 0; 
            uint gpio_G = 0; 
            uint gpio_R = 0; 
            uint port = 0;
            uint temp = 0x01;
            switch(LEDID)
            {
                case TCA6416_Constants.ENC_LED_GLOBE_ERR:
                    addr = TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
                    gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_8;
                    gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_9;
                    break;
                case TCA6416_Constants.ENC_LED_FAN:
                    addr = TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
                    gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_2;
                    gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_3;
                    break;


            }
            if ((gpio_G > 7) && (gpio_G <= TCA6416A_GPIO_MAX) ||
                (gpio_R > 7) && (gpio_R <= TCA6416A_GPIO_MAX))
            {
                gpio_G -= 8;
                gpio_R -= 8;
                port = TCA6416_Constants.TCA6416A_INPUT_PORT_1;
            }
            else
            {
                port = TCA6416_Constants.TCA6416A_INPUT_PORT_0;
            }
            tca6416a_get_gpio_port_value(addr, port, ref bitmap);

            switch (status)
            {
                case TCA6416_Constants.ENC_LED_GREEN:
                    bitmap |= temp << Convert.ToInt32(gpio_G);
                    bitmap &= ~(temp << Convert.ToInt32(gpio_R));
                    break;

                case TCA6416_Constants.ENC_LED_RED:
                    bitmap &= ~(temp << Convert.ToInt32(gpio_G));
                    bitmap |= temp << Convert.ToInt32(gpio_R);
                    break;

                case TCA6416_Constants.ENC_LED_AMBER:
                    bitmap |= temp << Convert.ToInt32(gpio_G);
                    bitmap |= temp << Convert.ToInt32(gpio_R);
                    break;

                case TCA6416_Constants.ENC_LED_OFF:
                case TCA6416_Constants.ENC_LED_DARK:
                    bitmap &= ~(temp << Convert.ToInt32(gpio_G));
                    bitmap &= ~(temp << Convert.ToInt32(gpio_R));
                    break;

                default:
                    //ENC_DBG_PRINT("Led get error status %d\n", status);
                    break;
            }
            tca6416a_set_gpio_port_value(addr, port, ref bitmap);
        }
    }
}
