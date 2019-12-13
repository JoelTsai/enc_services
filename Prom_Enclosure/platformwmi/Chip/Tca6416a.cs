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
	public class TCA6416
	{
        public static uint A21P0 = 0;
        public static uint A21P1 = 0;
        public static uint A20P0 = 0;
        public static uint A20P1 = 0;
        private const uint TCA6416A_GPIO_MAX = 15;
        //public PCHSMBUS SMB;
        public TCA6416()
		{
            //this.SMB = new PCHSMBUS();
            byte data_temp = 0x00;
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

		public int Tca6416a_write_value(uint addr, uint reg, ref byte data)
		{
			// return pch200_smbus_write(addr, reg, PCH_BYTE_DATA, data, BLEN);
			uint[] data_temp = { data };
            byte i=0;
            do
            {
                if (PCHSMBUS.WriteSMB(addr, reg, TCA6416_Constants.BLEN, ref data_temp) == 0)
                    return 0;
                i++;
            } while (i < 3);
            return -1;
		}

		public int Tca6416a_read_value(uint addr, uint reg, ref uint data)
		{

			//return pch200_smbus_read(addr, reg, PCH_BYTE_DATA, data, BLEN);
			uint[] data_temp = { data };
            byte i = 0;
            do
            {
                if (PCHSMBUS.ReadSMB(addr, reg, TCA6416_Constants.BLEN, ref data_temp) == 0)
                {
                    data = data_temp[0];
                    return 0;
                }
                i++;
            } while (i < 3);
			return -1;

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
            byte Bdata;
            uint temp = 0 ;
            byte count = 0;
			if (port == TCA6416_Constants.TCA6416A_PORT_0)
			{
				reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_0;
			}
			else if (port == TCA6416_Constants.TCA6416A_PORT_1)
			{
				reg = TCA6416_Constants.TCA6416A_OUTPUT_PORT_1;
			}
            Bdata = Convert.ToByte(data&0xFF);
            do
            {
                Tca6416a_write_value(addr, reg, ref Bdata);
                Tca6416a_read_value(addr, reg, ref temp);
                count++;
            } while(Bdata!=Convert.ToByte(temp & 0xFF) && count<3);
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
            switch (chipId)
            {
                case 0:
                    addr = TCA6416_Constants.TCA6416A_I2C_ADDR_LO;
                    if (port == TCA6416_Constants.TCA6416A_PORT_0)
                    {

                        A20P0 = PinId;
                        Console.WriteLine("A20P0={0}", A20P0);
                    }
                    else if (port == TCA6416_Constants.TCA6416A_PORT_1)
                    {

                        A20P1 = PinId;
                        Console.WriteLine("A20P1={0}", A20P1);
                    }
                    break;
                case 1:
                    addr = TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
                    if (Enclsoure.Enclsoure_class.Model_ID == Enclsoure.Enclsoure_class.Model_VA8020)
                    {
                        
                        if (port == TCA6416_Constants.TCA6416A_PORT_0)
                            {
                            uint temp = 1;
                            PinId &= TCA6416_Constants.FW_REQUEST_PORT0_MASK;
                            uint globe_gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_2;
                            uint globe_gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_3;
                            if ((PinId & TCA6416_Constants.FW_REQUEST_PORT0_MASK) == 0x20)
                                { Enclsoure.Enclsoure_class.GlobeError_LED_trigger = true; }
                                else
                                { Enclsoure.Enclsoure_class.GlobeError_LED_trigger = false; }

                                if (Enclsoure.Enclsoure_class.Fan_color == TCA6416_Constants.ENC_LED_RED ||
                                Enclsoure.Enclsoure_class.GlobeError_LED_trigger)
                                {
                                    PinId &= ~(temp << Convert.ToInt32(globe_gpio_G));
                                    PinId |= temp << Convert.ToInt32(globe_gpio_R);
                                }
                                else
                                {
                                    PinId |= temp << Convert.ToInt32(globe_gpio_G);
                                    PinId &= ~(temp << Convert.ToInt32(globe_gpio_R));
                                }
                            PinId |= 0x40;//POWER LED Enable
                            PinId |= Enclsoure.Enclsoure_class.OPAS_LED;
                            A21P0 = PinId;

                        }
                        if (port == TCA6416_Constants.TCA6416A_PORT_1)
                        {
                            PinId &= TCA6416_Constants.FW_REQUEST_PORT1_MASK;
                            uint Fan_gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_0;
                            uint FAN_gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_1;
                            uint temp = 1;

                            switch (Enclsoure.Enclsoure_class.Fan_color)
                            {
                                case TCA6416_Constants.ENC_LED_GREEN:
                                    PinId |= temp << Convert.ToInt32(Fan_gpio_G);
                                    PinId &= ~(temp << Convert.ToInt32(FAN_gpio_R));
                                    break;

                                case TCA6416_Constants.ENC_LED_RED:
                                    PinId &= ~(temp << Convert.ToInt32(Fan_gpio_G));
                                    PinId |= temp << Convert.ToInt32(FAN_gpio_R);
                                    break;

                                case TCA6416_Constants.ENC_LED_AMBER:
                                    PinId |= temp << Convert.ToInt32(Fan_gpio_G);
                                    PinId |= temp << Convert.ToInt32(FAN_gpio_R);
                                    break;

                                case TCA6416_Constants.ENC_LED_OFF:
                                case TCA6416_Constants.ENC_LED_DARK:
                                    PinId &= ~(temp << Convert.ToInt32(Fan_gpio_G));
                                    PinId &= ~(temp << Convert.ToInt32(FAN_gpio_R));
                                    break;

                                default:
                                    //ENC_DBG_PRINT("Led get error status %d\n", status);
                                    break;
                            }
                            PinId |= Enclsoure.Enclsoure_class.NET_LED;
                            A21P1 = PinId;
                        }
                    }
                    else
                    {
                        if (port == TCA6416_Constants.TCA6416A_PORT_0)
                        {
                            uint Fan_gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_2;
                            uint FAN_gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_3;
                            uint temp = 1;

                            PinId &= TCA6416_Constants.FW_REQUEST_PORT0_MASK;
                            switch (Enclsoure.Enclsoure_class.Fan_color)
                            {
                                case TCA6416_Constants.ENC_LED_GREEN:
                                    PinId |= temp << Convert.ToInt32(Fan_gpio_G);
                                    PinId &= ~(temp << Convert.ToInt32(FAN_gpio_R));
                                    break;

                                case TCA6416_Constants.ENC_LED_RED:
                                    PinId &= ~(temp << Convert.ToInt32(Fan_gpio_G));
                                    PinId |= temp << Convert.ToInt32(FAN_gpio_R);
                                    break;

                                case TCA6416_Constants.ENC_LED_AMBER:
                                    PinId |= temp << Convert.ToInt32(Fan_gpio_G);
                                    PinId |= temp << Convert.ToInt32(FAN_gpio_R);
                                    break;

                                case TCA6416_Constants.ENC_LED_OFF:
                                case TCA6416_Constants.ENC_LED_DARK:
                                    PinId &= ~(temp << Convert.ToInt32(Fan_gpio_G));
                                    PinId &= ~(temp << Convert.ToInt32(FAN_gpio_R));
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
                            A21P0 = PinId;

                        }
                        if (port == TCA6416_Constants.TCA6416A_PORT_1)
                        {
                            PinId &= TCA6416_Constants.FW_REQUEST_PORT1_MASK;
                            uint gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_0;
                            uint gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_1;
                            uint temp = 1;

                            if (Enclsoure.Enclsoure_class.Fan_color == TCA6416_Constants.ENC_LED_RED ||
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
                            A21P1 = PinId;
                        }
                    }
                    break;
			}
            if(Enclsoure.Enclsoure_class.Blink_trigger==false)
			tca6416a_set_gpio_port_value (addr, port, ref PinId);
			
			Console.WriteLine("encSetLedStatus End!");
		}

		public void encGetLedStatus(ref uint?[] Ledreg)
		{
            Ledreg[0] = A20P0 | (A20P1 << 16);
            Ledreg[1] = A21P0 | (A21P1 << 16);
            return;

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
            if (Enclsoure.Enclsoure_class.Model_ID == Enclsoure.Enclsoure_class.Model_VA8020)
            {
                switch (LEDID)
                {

                    case TCA6416_Constants.ENC_LED_FAN:
                        addr = TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
                        gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_8;
                        gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_9;
                        break;
                    case TCA6416_Constants.ENC_LED_GLOBE_ERR:
                        addr = TCA6416_Constants.TCA6416A_I2C_ADDR_HI;
                        gpio_G = TCA6416_Constants.TCA6416A_GPIO_PIN_2;
                        gpio_R = TCA6416_Constants.TCA6416A_GPIO_PIN_3;
                        break;
                }
            }
            else
            {
                switch (LEDID)
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
            if(port== TCA6416_Constants.TCA6416A_INPUT_PORT_1)
            {
                A21P1 = bitmap;
            }
            else if (port == TCA6416_Constants.TCA6416A_INPUT_PORT_0)
            {
                A21P0 = bitmap;
            }
            if (Enclsoure.Enclsoure_class.Blink_trigger == false)
                tca6416a_set_gpio_port_value(addr, port, ref bitmap);
        }
    }
}
