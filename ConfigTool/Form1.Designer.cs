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
            this.checkEncryption = new System.Windows.Forms.CheckBox();
            this.lblEncryptionKey = new System.Windows.Forms.Label();
            this.textEncryptionKey = new System.Windows.Forms.TextBox();
            this.buttonExit = new System.Windows.Forms.Button();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.label4 = new System.Windows.Forms.Label();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox5 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.textNetwork = new System.Windows.Forms.TextBox();
            this.lblNetwork = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonCreate
            // 
            this.buttonCreate.Location = new System.Drawing.Point(12, 377);
            this.buttonCreate.Name = "buttonCreate";
            this.buttonCreate.Size = new System.Drawing.Size(316, 23);
            this.buttonCreate.TabIndex = 6;
            this.buttonCreate.Text = "Create config file";
            this.buttonCreate.UseVisualStyleBackColor = true;
            this.buttonCreate.Click += new System.EventHandler(this.buttonCreate_Click);
            // 
            // textServerAddress
            // 
            this.textServerAddress.Location = new System.Drawing.Point(12, 80);
            this.textServerAddress.Name = "textServerAddress";
            this.textServerAddress.Size = new System.Drawing.Size(209, 20);
            this.textServerAddress.TabIndex = 3;
            this.textServerAddress.Text = "http://";
            // 
            // checkLLDP
            // 
            this.checkLLDP.AutoSize = true;
            this.checkLLDP.Checked = true;
            this.checkLLDP.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkLLDP.Location = new System.Drawing.Point(12, 12);
            this.checkLLDP.Name = "checkLLDP";
            this.checkLLDP.Size = new System.Drawing.Size(53, 17);
            this.checkLLDP.TabIndex = 1;
            this.checkLLDP.Text = "LLDP";
            this.checkLLDP.UseVisualStyleBackColor = true;
            // 
            // checkCDP
            // 
            this.checkCDP.AutoSize = true;
            this.checkCDP.Checked = true;
            this.checkCDP.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkCDP.Location = new System.Drawing.Point(12, 35);
            this.checkCDP.Name = "checkCDP";
            this.checkCDP.Size = new System.Drawing.Size(48, 17);
            this.checkCDP.TabIndex = 2;
            this.checkCDP.Text = "CDP";
            this.checkCDP.UseVisualStyleBackColor = true;
            // 
            // textTimeout
            // 
            this.textTimeout.Location = new System.Drawing.Point(259, 80);
            this.textTimeout.Name = "textTimeout";
            this.textTimeout.Size = new System.Drawing.Size(69, 20);
            this.textTimeout.TabIndex = 4;
            this.textTimeout.Text = "0";
            // 
            // lblTimeout
            // 
            this.lblTimeout.AutoSize = true;
            this.lblTimeout.Location = new System.Drawing.Point(256, 64);
            this.lblTimeout.Name = "lblTimeout";
            this.lblTimeout.Size = new System.Drawing.Size(67, 13);
            this.lblTimeout.TabIndex = 1;
            this.lblTimeout.Text = "Timeout (ms)";
            // 
            // lblServerAddress
            // 
            this.lblServerAddress.AutoSize = true;
            this.lblServerAddress.Location = new System.Drawing.Point(12, 64);
            this.lblServerAddress.Name = "lblServerAddress";
            this.lblServerAddress.Size = new System.Drawing.Size(78, 13);
            this.lblServerAddress.TabIndex = 8;
            this.lblServerAddress.Text = "Server address";
            // 
            // checkEncryption
            // 
            this.checkEncryption.AutoSize = true;
            this.checkEncryption.Enabled = false;
            this.checkEncryption.Location = new System.Drawing.Point(10, 186);
            this.checkEncryption.Name = "checkEncryption";
            this.checkEncryption.Size = new System.Drawing.Size(97, 17);
            this.checkEncryption.TabIndex = 9;
            this.checkEncryption.Text = "Use encryption";
            this.checkEncryption.UseVisualStyleBackColor = true;
            // 
            // lblEncryptionKey
            // 
            this.lblEncryptionKey.AutoSize = true;
            this.lblEncryptionKey.Enabled = false;
            this.lblEncryptionKey.Location = new System.Drawing.Point(12, 206);
            this.lblEncryptionKey.Name = "lblEncryptionKey";
            this.lblEncryptionKey.Size = new System.Drawing.Size(78, 13);
            this.lblEncryptionKey.TabIndex = 10;
            this.lblEncryptionKey.Text = "Encryption Key";
            // 
            // textEncryptionKey
            // 
            this.textEncryptionKey.Enabled = false;
            this.textEncryptionKey.Location = new System.Drawing.Point(12, 222);
            this.textEncryptionKey.Name = "textEncryptionKey";
            this.textEncryptionKey.Size = new System.Drawing.Size(209, 20);
            this.textEncryptionKey.TabIndex = 11;
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(12, 406);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(316, 23);
            this.buttonExit.TabIndex = 7;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // buttonLoad
            // 
            this.buttonLoad.Location = new System.Drawing.Point(10, 348);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(318, 23);
            this.buttonLoad.TabIndex = 5;
            this.buttonLoad.Text = "Load config file";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 250);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(182, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Extra data to include in server upload";
            // 
            // checkBox4
            // 
            this.checkBox4.AutoSize = true;
            this.checkBox4.Location = new System.Drawing.Point(12, 277);
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.Size = new System.Drawing.Size(74, 17);
            this.checkBox4.TabIndex = 13;
            this.checkBox4.Text = "Hostname";
            this.checkBox4.UseVisualStyleBackColor = true;
            // 
            // checkBox5
            // 
            this.checkBox5.AutoSize = true;
            this.checkBox5.Location = new System.Drawing.Point(12, 300);
            this.checkBox5.Name = "checkBox5";
            this.checkBox5.Size = new System.Drawing.Size(90, 17);
            this.checkBox5.TabIndex = 14;
            this.checkBox5.Text = "MAC Address";
            this.checkBox5.UseVisualStyleBackColor = true;
            // 
            // checkBox6
            // 
            this.checkBox6.AutoSize = true;
            this.checkBox6.Location = new System.Drawing.Point(12, 324);
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.Size = new System.Drawing.Size(77, 17);
            this.checkBox6.TabIndex = 15;
            this.checkBox6.Text = "IP Address";
            this.checkBox6.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            this.checkBox7.AutoSize = true;
            this.checkBox7.Location = new System.Drawing.Point(137, 277);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(71, 17);
            this.checkBox7.TabIndex = 16;
            this.checkBox7.Text = "Switch IP";
            this.checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            this.checkBox8.AutoSize = true;
            this.checkBox8.Location = new System.Drawing.Point(137, 301);
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.Size = new System.Drawing.Size(84, 17);
            this.checkBox8.TabIndex = 17;
            this.checkBox8.Text = "Switchname";
            this.checkBox8.UseVisualStyleBackColor = true;
            // 
            // checkBox9
            // 
            this.checkBox9.AutoSize = true;
            this.checkBox9.Location = new System.Drawing.Point(137, 324);
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.Size = new System.Drawing.Size(68, 17);
            this.checkBox9.TabIndex = 18;
            this.checkBox9.Text = "VLAN ID";
            this.checkBox9.UseVisualStyleBackColor = true;
            // 
            // textNetwork
            // 
            this.textNetwork.Location = new System.Drawing.Point(12, 129);
            this.textNetwork.Name = "textNetwork";
            this.textNetwork.Size = new System.Drawing.Size(69, 20);
            this.textNetwork.TabIndex = 19;
            // 
            // lblNetwork
            // 
            this.lblNetwork.AutoSize = true;
            this.lblNetwork.Location = new System.Drawing.Point(12, 113);
            this.lblNetwork.Name = "lblNetwork";
            this.lblNetwork.Size = new System.Drawing.Size(145, 13);
            this.lblNetwork.TabIndex = 20;
            this.lblNetwork.Text = "First octet of network adapter";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(340, 441);
            this.Controls.Add(this.lblNetwork);
            this.Controls.Add(this.textNetwork);
            this.Controls.Add(this.checkBox9);
            this.Controls.Add(this.checkBox8);
            this.Controls.Add(this.checkBox7);
            this.Controls.Add(this.checkBox6);
            this.Controls.Add(this.checkBox5);
            this.Controls.Add(this.checkBox4);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.textEncryptionKey);
            this.Controls.Add(this.lblEncryptionKey);
            this.Controls.Add(this.checkEncryption);
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
        private System.Windows.Forms.CheckBox checkEncryption;
        private System.Windows.Forms.Label lblEncryptionKey;
        private System.Windows.Forms.TextBox textEncryptionKey;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox checkBox4;
        private System.Windows.Forms.CheckBox checkBox5;
        private System.Windows.Forms.CheckBox checkBox6;
        private System.Windows.Forms.CheckBox checkBox7;
        private System.Windows.Forms.CheckBox checkBox8;
        private System.Windows.Forms.CheckBox checkBox9;
        private System.Windows.Forms.TextBox textNetwork;
        private System.Windows.Forms.Label lblNetwork;
    }
}

