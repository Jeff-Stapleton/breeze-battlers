/*
	Rahs Tool Suite 1.0.0
	-----
	SaxonRah - Robert Chubb @ ParabolicLabs - 30/11/2014 - 3:36 AM
*/

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(XLLog, Log, All)

class ExtendedLibraryModule : public IModuleInterface
{
private:

public:
	ExtendedLibraryModule();
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};