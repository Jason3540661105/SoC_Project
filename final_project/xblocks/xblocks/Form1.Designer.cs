namespace xblocks
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
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
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
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
        /// 修改這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label_info = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.label213 = new System.Windows.Forms.Label();
            this.label_block_count = new System.Windows.Forms.Label();
            this.label_score = new System.Windows.Forms.Label();
            this.label_level = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label_info
            // 
            this.label_info.AutoSize = true;
            this.label_info.Font = new System.Drawing.Font("新細明體", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label_info.ForeColor = System.Drawing.Color.Red;
            this.label_info.Location = new System.Drawing.Point(507, 458);
            this.label_info.Name = "label_info";
            this.label_info.Size = new System.Drawing.Size(0, 27);
            this.label_info.TabIndex = 200;
            // 
            // button1
            // 
            this.button1.Enabled = false;
            this.button1.Font = new System.Drawing.Font("新細明體", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.button1.Location = new System.Drawing.Point(231, 249);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(165, 57);
            this.button1.TabIndex = 201;
            this.button1.TabStop = false;
            this.button1.Text = "New Game";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Visible = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label213
            // 
            this.label213.AutoSize = true;
            this.label213.Font = new System.Drawing.Font("新細明體", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label213.Location = new System.Drawing.Point(520, 179);
            this.label213.Name = "label213";
            this.label213.Size = new System.Drawing.Size(50, 22);
            this.label213.TabIndex = 214;
            this.label213.Text = "Next";
            // 
            // label_block_count
            // 
            this.label_block_count.AutoSize = true;
            this.label_block_count.Font = new System.Drawing.Font("新細明體", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label_block_count.Location = new System.Drawing.Point(508, 319);
            this.label_block_count.Name = "label_block_count";
            this.label_block_count.Size = new System.Drawing.Size(73, 22);
            this.label_block_count.TabIndex = 215;
            this.label_block_count.Text = "Blocks:";
            // 
            // label_score
            // 
            this.label_score.AutoSize = true;
            this.label_score.Font = new System.Drawing.Font("新細明體", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label_score.Location = new System.Drawing.Point(510, 359);
            this.label_score.Name = "label_score";
            this.label_score.Size = new System.Drawing.Size(62, 22);
            this.label_score.TabIndex = 216;
            this.label_score.Text = "Score:";
            // 
            // label_level
            // 
            this.label_level.AutoSize = true;
            this.label_level.Font = new System.Drawing.Font("新細明體", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label_level.Location = new System.Drawing.Point(510, 399);
            this.label_level.Name = "label_level";
            this.label_level.Size = new System.Drawing.Size(63, 22);
            this.label_level.TabIndex = 217;
            this.label_level.Text = "Level:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(697, 652);
            this.Controls.Add(this.label_level);
            this.Controls.Add(this.label_score);
            this.Controls.Add(this.label_block_count);
            this.Controls.Add(this.label213);
            this.Controls.Add(this.label_info);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "xblocks";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyUp);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label_info;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label213;
        private System.Windows.Forms.Label label_block_count;
        private System.Windows.Forms.Label label_score;
        private System.Windows.Forms.Label label_level;
    }
}

