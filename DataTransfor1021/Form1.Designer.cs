namespace DataTransfor
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
            this.xAxis = new HslCommunication.Controls.UserCurve();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.startObservation = new HslCommunication.Controls.UserButton();
            this.HallText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // xAxis
            // 
            this.xAxis.BackColor = System.Drawing.Color.Transparent;
            this.xAxis.Location = new System.Drawing.Point(108, 237);
            this.xAxis.Name = "xAxis";
            this.xAxis.Size = new System.Drawing.Size(589, 197);
            this.xAxis.TabIndex = 0;
            this.xAxis.ValueMaxLeft = 3000F;
            this.xAxis.ValueMaxRight = 3000F;
            this.xAxis.ValueMinLeft = 1000F;
            this.xAxis.ValueMinRight = 1000F;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Times New Roman", 12F);
            this.label1.Location = new System.Drawing.Point(132, 215);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 19);
            this.label1.TabIndex = 5;
            this.label1.Text = "X軸數值";
            // 
            // startObservation
            // 
            this.startObservation.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.startObservation.BackColor = System.Drawing.Color.Transparent;
            this.startObservation.CustomerInformation = "";
            this.startObservation.EnableColor = System.Drawing.Color.FromArgb(((int)(((byte)(190)))), ((int)(((byte)(190)))), ((int)(((byte)(190)))));
            this.startObservation.Font = new System.Drawing.Font("微软雅黑", 12F);
            this.startObservation.Location = new System.Drawing.Point(619, 691);
            this.startObservation.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.startObservation.Name = "startObservation";
            this.startObservation.Size = new System.Drawing.Size(78, 25);
            this.startObservation.TabIndex = 8;
            this.startObservation.UIText = "開始觀測";
            this.startObservation.Click += new System.EventHandler(this.StartObservation_Click);
            // 
            // HallText
            // 
            this.HallText.AllowDrop = true;
            this.HallText.Location = new System.Drawing.Point(761, 257);
            this.HallText.MaxLength = 100000000;
            this.HallText.Multiline = true;
            this.HallText.Name = "HallText";
            this.HallText.ReadOnly = true;
            this.HallText.ScrollBars = System.Windows.Forms.ScrollBars.Horizontal;
            this.HallText.Size = new System.Drawing.Size(386, 371);
            this.HallText.TabIndex = 9;
            this.HallText.TextChanged += new System.EventHandler(this.HallText_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Times New Roman", 12F);
            this.label2.Location = new System.Drawing.Point(757, 215);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 19);
            this.label2.TabIndex = 5;
            this.label2.Text = "輪速感測器";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("新細明體", 20F);
            this.label3.Location = new System.Drawing.Point(167, 514);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(74, 27);
            this.label3.TabIndex = 10;
            this.label3.Text = "label3";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("新細明體", 20F);
            this.label4.Location = new System.Drawing.Point(307, 514);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(74, 27);
            this.label4.TabIndex = 11;
            this.label4.Text = "label4";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(1350, 729);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.HallText);
            this.Controls.Add(this.startObservation);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.xAxis);
            this.Name = "Form1";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.Text = "數值監控";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private HslCommunication.Controls.UserCurve xAxis;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label label1;
        private HslCommunication.Controls.UserButton startObservation;
        private System.Windows.Forms.TextBox HallText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
    }
}

