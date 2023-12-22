using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Sokoban_Game
{
    public partial class Form1 : Form
    {
        public Task ReceiveSerial;

        StringBuilder port = new StringBuilder();
        SerialPort SerialPort = new SerialPort();
        string text = "Is Working!";
        

        public Form1()
        {
            InitializeComponent();
            SerialPortSelect.Items.AddRange(SerialPort.GetPortNames());
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void SerialPortSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            port.Append(SerialPortSelect.Text);
        }

        private void SerialPortConnect_Click(object sender, EventArgs e)
        {
            try
            {
                SerialPort.PortName = port.ToString();
                SerialPort.BaudRate = 115200;
                SerialPort.Parity = Parity.None;
                SerialPort.DataBits = 8;
                SerialPort.StopBits = StopBits.One;
                SerialPort.Open();
                SerialPortConnect.Enabled = false;
                SerialPortDisconnect.Enabled = true;

                if (SerialPort.IsOpen)
                {
                    Console.WriteLine(text + "Port is : " + SerialPort.PortName);
                    Receive_Data();
                }
            }
            catch (Exception exex)
            {
                MessageBox.Show(exex.Message);
                SerialPort.Close();

            }
        }

        private void SerialPortDisconnect_Click(object sender, EventArgs e)
        {
            SerialPortSelect.Enabled = true;
            SerialPortConnect.Enabled = false;
            SerialPort.Close();
        }

        private void Receive_Data()
        {
            try
            {
                ReceiveSerial = new Task(Receive_Data_available);

                ReceiveSerial.Start();
            }
            catch (Exception exec)
            {
                MessageBox.Show(exec.Message);
            }
        }

        private void Receive_Data_available()
        {
            int number = 73;                                   // 設定接收的位元組數量
            byte[] ReceiveData = new byte[number];

            while (SerialPort.IsOpen)
            {
                if (SerialPort.BytesToRead >= number)
                {
                    SerialPort.Read(ReceiveData, 0, number); // 讀取接收的資料到位元組陣列中

                    string receivedText = Encoding.ASCII.GetString(ReceiveData); // 將位元組陣列轉換為字串

                    UpdateRichTextBox(receivedText); // 更新 RichTextBox 中的文字
                }
            }
        }

        private void UpdateRichTextBox(string text)
        {
            if (uart_richTextBox_test.InvokeRequired)
            {
                uart_richTextBox_test.Invoke(new Action<string>(UpdateRichTextBox), text); // 在 UI 線程中更新 RichTextBox
            }
            else
            {
                uart_richTextBox_test.AppendText(text + Environment.NewLine); // 將接收到的資料顯示在 RichTextBox 中並換行
            }
        }
    }
}
