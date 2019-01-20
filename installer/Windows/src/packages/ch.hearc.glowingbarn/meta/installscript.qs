function Component()
{
	var programFiles = installer.environmentVariable("ProgramFiles");
    if (programFiles != "" && installer.value("os") === "win")
         installer.setValue("TargetDir", programFiles + "/MagnAndCie");
}

Component.prototype.isDefault = function()
{
	return true;
}

Component.prototype.createOperations = function()
{
	try
	{
		component.createOperations();
	}
	catch (e)
	{
		print(e);
	}
	
	if (installer.value("os") === "win")
	{
		component.addOperation("CreateShortcut", "@TargetDir@/glowing-barn.exe", "@DesktopDir@/Magn & Cie.lnk");
	}
}