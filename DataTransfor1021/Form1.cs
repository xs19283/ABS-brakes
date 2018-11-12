using System;
using System.Drawing;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Text;
using System.Threading;
using System.Linq;
using System.Windows.Forms;
using Timer = System.Windows.Forms.Timer;
using System.IO;
using System.IO.Ports;

namespace DataTransfor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int[] AxisModBusData = new int[4];
        ushort[] HallModBusData = new ushort[4];
        ushort HallData;
        int AxisData;
        int count;

        private Boolean receiving;
        private SerialPort comport;
        private Thread t;

        delegate void Display(Byte[] buffer);

        ////////IO文字
        private void WriteTimeData()
        {
            StreamWriter sw = new StreamWriter(@"D:\Users\IIIT\Desktop\Data.txt", true);
            DateTime saveNow = DateTime.Now;
            //sw.WriteLine(saveNow.ToString("hh:mm:ss.ff") + " 三軸數值 : " + AxisData + " 輪速感測器 : " + HallData);
            sw.WriteLine(AxisData);
            sw.Close();
        }

        ////////程式一執行做藍芽serialPort初始化, 以及曲線圖初始化
        private void Form1_Load(object sender, EventArgs e)
        {
            SerialPortInit(sender, e);
            InitGraph(sender, e);
        }

        ////////SerialPort初始化  (確認 COM PORT 有無正確)
        private void SerialPortInit(object sender, EventArgs e)
        {
            comport = new SerialPort("COM10", 9600, Parity.None, 8, StopBits.One);
            if (!comport.IsOpen)
            {
                comport.Open();
                receiving = true;
                t = new Thread(DoReceive);
                t.IsBackground = true;
                t.Start();
            }
        }

        ////////曲線圖初始化
        private void InitGraph(object sender, EventArgs e)
        {
            xAxis.SetLeftCurve("A", new float[] { }, Color.Tomato);
        }

        ////////X軸資料顯示
        private void XAxisValueShow(object sender, EventArgs e)
        {
            Timer timer = new Timer
            {
                Interval = 50  //10毫秒更新一次
            };
            timer.Tick += (sender1, e1) =>
            {
                xAxis.AddCurveData("A", AxisData);
            };
            timer.Start();
        }


        ////////開始觀測
        private void StartObservation_Click(object sender, EventArgs e)
        {
            XAxisValueShow(sender, e);
        }

        private void ThreadText()
        {
            String data = Convert.ToString(HallData);
            SetText(HallText.Text + "\t" + data);
        }

        delegate void SetTextCallback(string text);
        private void SetText(String text)
        {
            if (this.HallText.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.HallText.Text = text;
            }
        }
        private void DoReceive()
        {
            Boolean ctrl = true;
            while (ctrl)
            {
                int b = comport.ReadByte();
                if (b == 3)
                {
                    for (int i = 0; i < 9; i++)
                    {
                        comport.ReadByte();
                    }
                    ctrl = false;
                }
            }
            Byte[] buffer = new Byte[5];
            while (receiving)
            {
                while (comport.BytesToRead < 5)
                {
                    //Thread.Sleep(8);
                }
                Int32 length = comport.Read(buffer, 0, buffer.Length);
                if (buffer[0] == 3 && buffer[0] + buffer[1] == buffer[4])
                {
                    AxisData = (ushort)(buffer[1] << 8);
                    AxisData += buffer[2];
                    count = buffer[3];
                }

                if (buffer[0] == 85 && buffer[0] + buffer[1] == buffer[4])
                {
                    HallData = (ushort)(buffer[1] << 8);
                    HallData += buffer[2];
                }
                WriteTimeData();
                ThreadText();
                //Thread.Sleep(16);

            }
        }
        private void HallText_TextChanged(object sender, EventArgs e)
        {
            this.HallText.SelectionStart = this.HallText.Text.Length;
            this.HallText.ScrollToCaret();
        }
    }
}


//sbyte CRC;
//byte sum;
//SerialPort sp = (SerialPort)sender;
// if (sp.BytesToRead >= 5)
// {
//   byte[] bufferData = new byte[sp.BytesToRead];
//   sp.Read(bufferData, 0, bufferData.Length);

//  if (bufferData[0] == 3 && bufferData[0] + bufferData[1] == bufferData[4])
// {
/*for (int i = 1; i < 4; i++)
{
    AxisModBusData[i - 1] = bufferData[i];
}*/
// sum = Convert.ToByte(AxisModBusData[0] + 3);
//  CRC = Convert.ToSByte((sbyte)~sum);
//   CRC++;
// if (CRC == AxisModBusData[1021])
//{
//AxisData = (ushort)(bufferData[1] << 8);
// AxisData += bufferData[2];
// count = bufferData[3];
//}
// }

//if (bufferData[0] == 2 && bufferData[0] + bufferData[1] == bufferData[4])
//{
/*for (int i = 1; i < 4; i++)
{
    HallModBusData[i - 1] = bufferData[i];
}*/
//sum = Convert.ToByte(HallModBusData[0] + 2);
//CRC = ~sum + 1;
//if (CRC == HallModBusData[1])
//{
//    HallData = bufferData[1];
//}
//HallData = (ushort)(bufferData[1] << 8);
// HallData += bufferData[2];
//  }
// }
// }
// WriteTimeData();
//ThreadText();






