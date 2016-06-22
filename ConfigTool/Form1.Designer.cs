namespace ConfigTool
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.buttonCreate = new System.Windows.Forms.Button();
            this.textServerAddress = new System.Windows.Forms.TextBox();
            this.checkLLDP = new System.Windows.Forms.CheckBox();
            this.checkCDP = new System.Windows.Forms.CheckBox();
            this.textTimeout = new System.Windows.Forms.TextBox();
            this.lblTimeout = new System.Windows.Forms.Label();
            this.lblServerAddress = new System.Windows.Forms.Label();
            this.buttonExit = new System.Windows.Forms.Button();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.textNetwork = new System.Windows.Forms.TextBox();
            this.lblNetwork = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textPage = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.radioSimple = new System.Windows.Forms.RadioButton();
            this.radioCSV = new System.Windows.Forms.RadioButton();
            this.checkLocal = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // buttonCreate
            // 
            this.buttonCreate.Location = new System.Drawing.Point(14, 378);
            this.buttonCreate.Name = "buttonCreate";
            this.buttonCreate.Size = new System.Drawing.Size(308, 23);
            this.buttonCreate.TabIndex = 14;
            this.buttonCreate.Text = "Create config file";
            this.buttonCreate.UseVisualStyleBackColor = true;
            this.buttonCreate.Click += new System.EventHandler(this.buttonCreate_Click);
            // 
            // textServerAddress
            // 
            this.textServerAddress.Location = new System.Drawing.Point(12, 127);
            this.textServerAddress.Name = "textServerAddress";
            this.textServerAddress.Size = new System.Drawing.Size(108, 20);
            this.textServerAddress.TabIndex = 1;
            // 
            // checkLLDP
            // 
            this.checkLLDP.AutoSize = true;
            this.checkLLDP.Checked = true;
            this.checkLLDP.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkLLDP.Location = new System.Drawing.Point(12, 217);
            this.checkLLDP.Name = "checkLLDP";
            this.checkLLDP.Size = new System.Drawing.Size(53, 17);
            this.checkLLDP.TabIndex = 5;
            this.checkLLDP.Text = "LLDP";
            this.checkLLDP.UseVisualStyleBackColor = true;
            // 
            // checkCDP
            // 
            this.checkCDP.AutoSize = true;
            this.checkCDP.Checked = true;
            this.checkCDP.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkCDP.Location = new System.Drawing.Point(71, 216);
            this.checkCDP.Name = "checkCDP";
            this.checkCDP.Size = new System.Drawing.Size(48, 17);
            this.checkCDP.TabIndex = 6;
            this.checkCDP.Text = "CDP";
            this.checkCDP.UseVisualStyleBackColor = true;
            // 
            // textTimeout
            // 
            this.textTimeout.Location = new System.Drawing.Point(234, 127);
            this.textTimeout.Name = "textTimeout";
            this.textTimeout.Size = new System.Drawing.Size(88, 20);
            this.textTimeout.TabIndex = 3;
            this.textTimeout.Text = "0";
            // 
            // lblTimeout
            // 
            this.lblTimeout.AutoSize = true;
            this.lblTimeout.Location = new System.Drawing.Point(231, 111);
            this.lblTimeout.Name = "lblTimeout";
            this.lblTimeout.Size = new System.Drawing.Size(94, 13);
            this.lblTimeout.TabIndex = 1;
            this.lblTimeout.Text = "Timeout (seconds)";
            // 
            // lblServerAddress
            // 
            this.lblServerAddress.AutoSize = true;
            this.lblServerAddress.Location = new System.Drawing.Point(9, 111);
            this.lblServerAddress.Name = "lblServerAddress";
            this.lblServerAddress.Size = new System.Drawing.Size(78, 13);
            this.lblServerAddress.TabIndex = 8;
            this.lblServerAddress.Text = "Server address";
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(14, 407);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(308, 23);
            this.buttonExit.TabIndex = 15;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(14, 349);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(308, 23);
            this.buttonLoad.TabIndex = 13;
            this.buttonLoad.Text = "Load config file";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // textNetwork
            // 
            this.textNetwork.Location = new System.Drawing.Point(12, 177);
            this.textNetwork.Name = "textNetwork";
            this.textNetwork.Size = new System.Drawing.Size(70, 20);
            this.textNetwork.TabIndex = 4;
            // 
            // lblNetwork
            // 
            this.lblNetwork.AutoSize = true;
            this.lblNetwork.Location = new System.Drawing.Point(9, 161);
            this.lblNetwork.Name = "lblNetwork";
            this.lblNetwork.Size = new System.Drawing.Size(146, 13);
            this.lblNetwork.TabIndex = 20;
            this.lblNetwork.Text = "First octet of network address";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(126, 111);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 13);
            this.label1.TabIndex = 21;
            this.label1.Text = "Page";
            // 
            // textPage
            // 
            this.textPage.Location = new System.Drawing.Point(128, 127);
            this.textPage.Name = "textPage";
            this.textPage.Size = new System.Drawing.Size(100, 20);
            this.textPage.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 200);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(99, 13);
            this.label2.TabIndex = 23;
            this.label2.Text = "Capture data using ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 63);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(325, 39);
            this.label3.TabIndex = 24;
            this.label3.Text = "Enter the IP address and page to submit data to.\nExample: http://10.0.0.1/index.p" +
    "hp would require you to put \n10.0.0.1 in the server address field and /index.php" +
    " in the page field.";
            // 
            // radioSimple
            // 
            this.radioSimple.AutoSize = true;
            this.radioSimple.Enabled = false;
            this.radioSimple.Location = new System.Drawing.Point(15, 287);
            this.radioSimple.Name = "radioSimple";
            this.radioSimple.Size = new System.Drawing.Size(102, 17);
            this.radioSimple.TabIndex = 8;
            this.radioSimple.TabStop = true;
            this.radioSimple.Text = "Text file (Simple)";
            this.radioSimple.UseVisualStyleBackColor = true;
            // 
            // radioCSV
            // 
            this.radioCSV.AutoSize = true;
            this.radioCSV.Enabled = false;
            this.radioCSV.Location = new System.Drawing.Point(15, 311);
            this.radioCSV.Name = "radioCSV";
            this.radioCSV.Size = new System.Drawing.Size(92, 17);
            this.radioCSV.TabIndex = 9;
            this.radioCSV.TabStop = true;
            this.radioCSV.Text = "Text file (CSV)";
            this.radioCSV.UseVisualStyleBackColor = true;
            // 
            // checkLocal
            // 
            this.checkLocal.AutoSize = true;
            this.checkLocal.Location = new System.Drawing.Point(13, 255);
            this.checkLocal.Name = "checkLocal";
            this.checkLocal.Size = new System.Drawing.Size(203, 17);
            this.checkLocal.TabIndex = 7;
            this.checkLocal.Text = "Use manually (ignores server settings)";
            this.checkLocal.UseVisualStyleBackColor = true;
            this.checkLocal.CheckedChanged += new System.EventHandler(this.checkLocal_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(340, 441);
            this.Controls.Add(this.checkLocal);
            this.Controls.Add(this.radioCSV);
            this.Controls.Add(this.radioSimple);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textPage);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblNetwork);
            this.Controls.Add(this.textNetwork);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.lblServerAddress);
            this.Controls.Add(this.lblTimeout);
            this.Controls.Add(this.textTimeout);
            this.Controls.Add(this.checkCDP);
            this.Controls.Add(this.checkLLDP);
            this.Controls.Add(this.textServerAddress);
            this.Controls.Add(this.buttonCreate);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(356, 480);
            this.MinimumSize = new System.Drawing.Size(356, 480);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Lanmap Configuration Tool v1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonCreate;
        private System.Windows.Forms.TextBox textServerAddress;
        private System.Windows.Forms.CheckBox checkLLDP;
        private System.Windows.Forms.CheckBox checkCDP;
        private System.Windows.Forms.TextBox textTimeout;
        private System.Windows.Forms.Label lblTimeout;
        private System.Windows.Forms.Label lblServerAddress;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.TextBox textNetwork;
        private System.Windows.Forms.Label lblNetwork;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textPage;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RadioButton radioSimple;
        private System.Windows.Forms.RadioButton radioCSV;
        private System.Windows.Forms.CheckBox checkLocal;
    }
}

