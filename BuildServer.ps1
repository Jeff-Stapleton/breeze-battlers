Param(
  [string]$uprojectLocation,
  [string]$outputDirectory,
  [string]$platform
)

RunUAT BuildCookRun -project="C:\Users\jeffd\Documents\GitHub\IO\IO.uproject" -noP4 -platform=Win64 -clientconfig=Shipping -serverconfig=Shipping -cook -server -serverplatform=Win64 -noclient -build -stage -pak -archive -archivedirectory="C:\IODist"