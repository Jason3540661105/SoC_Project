namespace Sokoban_Game
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置受控資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.SerialPortConnect = new System.Windows.Forms.Button();
            this.SerialPortDisconnect = new System.Windows.Forms.Button();
            this.comport_label = new System.Windows.Forms.Label();
            this.SerialPortSelect = new System.Windows.Forms.ComboBox();
            this.uart_richTextBox_test = new System.Windows.Forms.RichTextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.uart_textBox_test = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // SerialPortConnect
            // 
            this.SerialPortConnect.Font = new System.Drawing.Font("新細明體", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SerialPortConnect.Location = new System.Drawing.Point(336, 22);
            this.SerialPortConnect.Name = "SerialPortConnect";
            this.SerialPortConnect.Size = new System.Drawing.Size(153, 72);
            this.SerialPortConnect.TabIndex = 0;
            this.SerialPortConnect.Text = "Connect";
            this.SerialPortConnect.UseVisualStyleBackColor = true;
            this.SerialPortConnect.Click += new System.EventHandler(this.SerialPortConnect_Click);
            // 
            // SerialPortDisconnect
            // 
            this.SerialPortDisconnect.Font = new System.Drawing.Font("新細明體", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SerialPortDisconnect.Location = new System.Drawing.Point(539, 22);
            this.SerialPortDisconnect.Name = "SerialPortDisconnect";
            this.SerialPortDisconnect.Size = new System.Drawing.Size(153, 72);
            this.SerialPortDisconnect.TabIndex = 1;
            this.SerialPortDisconnect.Text = "Disconnect";
            this.SerialPortDisconnect.UseVisualStyleBackColor = true;
            this.SerialPortDisconnect.Click += new System.EventHandler(this.SerialPortDisconnect_Click);
            // 
            // comport_label
            // 
            this.comport_label.AutoSize = true;
            this.comport_label.Font = new System.Drawing.Font("新細明體", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.comport_label.Location = new System.Drawing.Point(29, 47);
            this.comport_label.Name = "comport_label";
            this.comport_label.Size = new System.Drawing.Size(128, 23);
            this.comport_label.TabIndex = 2;
            this.comport_label.Text = "COM PORT";
            // 
            // SerialPortSelect
            // 
            this.SerialPortSelect.FormattingEnabled = true;
            this.SerialPortSelect.Location = new System.Drawing.Point(180, 47);
            this.SerialPortSelect.Name = "SerialPortSelect";
            this.SerialPortSelect.Size = new System.Drawing.Size(121, 23);
            this.SerialPortSelect.TabIndex = 3;
            this.SerialPortSelect.SelectedIndexChanged += new System.EventHandler(this.SerialPortSelect_SelectedIndexChanged);
            // 
            // uart_richTextBox_test
            // 
            this.uart_richTextBox_test.Location = new System.Drawing.Point(33, 114);
            this.uart_richTextBox_test.Name = "uart_richTextBox_test";
            this.uart_richTextBox_test.Size = new System.Drawing.Size(659, 192);
            this.uart_richTextBox_test.TabIndex = 4;
            this.uart_richTextBox_test.Text = "";
            // 
            // uart_textBox_test
            // 
            this.uart_textBox_test.Location = new System.Drawing.Point(33, 329);
            this.uart_textBox_test.Name = "uart_textBox_test";
            this.uart_textBox_test.Size = new System.Drawing.Size(659, 25);
            this.uart_textBox_test.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(743, 366);
            this.Controls.Add(this.uart_textBox_test);
            this.Controls.Add(this.uart_richTextBox_test);
            this.Controls.Add(this.SerialPortSelect);
            this.Controls.Add(this.comport_label);
            this.Controls.Add(this.SerialPortDisconnect);
            this.Controls.Add(this.SerialPortConnect);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button SerialPortConnect;
        private System.Windows.Forms.Button SerialPortDisconnect;
        private System.Windows.Forms.Label comport_label;
        private System.Windows.Forms.ComboBox SerialPortSelect;
        private System.Windows.Forms.RichTextBox uart_richTextBox_test;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TextBox uart_textBox_test;
    }
}

