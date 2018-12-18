function Component()
{
    generateTr();
}

function generateTr() {
    component.setValue("DisplayName", qsTr("Snake"));
    component.setValue("Description", qsTr("This package contains Snake"));
}


Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();

    if (!component.isUninstalled()) {
        console.log("remove icons!!!");

        if (systemInfo.kernelType === "winnt") {
            console.log("create icons!!! on Windows");
            component.addOperation("Delete",
                                   "@DesktopDir@/@Name@.lnk");
        }

        console.log("remove icons!!!");

        if (systemInfo.kernelType === "linux") {

            console.log("create icons!!! on LINUX");
            component.addOperation("Delete",
                                   "@HomeDir@/.local/share/applications/@Name@.desktop");
            component.addOperation("Delete",
                                   "@HomeDir@/Desktop/@Name@.desktop");

            console.log("remove icons!!! on LINUX done");
        }

    } else {
        console.log("create icons!!!");

        if (systemInfo.kernelType === "winnt") {

            console.log("create icons!!! on Windows");
            component.addOperation("CreateShortcut",
                                   "@TargetDir@/snake.exe",
                                   "@DesktopDir@/@Name@.lnk");
        }

        console.log("create icons!!!");

        if (systemInfo.kernelType === "linux") {
            console.log("create icons!!! on LINUX");
            component.addOperation("CreateDesktopEntry",
                                   "@HomeDir@/.local/share/applications/@Name@.desktop",
                                   "Version=@Version@\n
                                    Type=Application\n
                                    Terminal=false\n
                                    Exec=@TargetDir@/snake.sh\n
                                    Name=@Name@\n
                                    Icon=@TargetDir@/icons/icon.png\n
                                    Name[en_US]=@Name@");

            console.log("create icons!!! on LINUX done");
        }
    }
}
