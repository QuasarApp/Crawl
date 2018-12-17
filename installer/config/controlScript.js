function Controller()
{
    generateTr();


    installer.setMessageBoxAutomaticAnswer("OverwriteTargetDirectory", QMessageBox.Yes);
    installer.uninstallationFinished.connect(this, Controller.prototype.uninstallationFinished);
    installer.installationFinished.connect(this, Controller.prototype.installationFinished);
}

function generateTr() {
    console.log("generate tr start ")

    installer.setValue("Name", qsTr("Noisier"));
    installer.setValue("Title", qsTr("Install Noisier"));
}


Controller.prototype.uninstallationFinished = function()
{

}


Controller.prototype.installationFinished = function()
{

}
