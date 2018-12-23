// Constructor
function Component()
{
    generateTr();
}

function generateTr() {
    console.log("generate tr start ")

    component.setValue("DisplayName", qsTr("Installer"));
    component.setValue("Description", qsTr("This package contains information of installer"));
}

function nativeSeparator() {
    if (installer.value("os") === "win") {
        return '\\';
    }
    return '/'
}

function isNoEmpty(dir){
    var libsArray = installer.findPath("*", [dir]);
    return Boolean(libsArray.length);
}

