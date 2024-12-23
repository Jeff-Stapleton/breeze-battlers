#addin "Cake.AWS.S3"
#addin "Cake.FileHelpers"
#addin "Cake.Powershell"

//--------------------------- ARGUMENTS ---------------------------//

var target = Argument("target", "All");
var uprojectLocation = Argument("uprojectLocation", "C:\\Users\\jeffd\\Documents\\GitHub\\IO\\IO.uproject");
var outputDirectory = Argument("outputDirectory", "C:\\IODist");
var serverPlatform = Argument("platform", "Win64");
var clientPlatform = Argument("platform", "Win64");
var awsAccessKey = Argument("awsAccessKey", "your key here");
var awsSecretKey = Argument("awsSecretKey", "your key here");
var s3Region = Argument("s3Region",  RegionEndpoint.USWest1);
var bucketName = Argument("bucketName", "cgs-main");

//----------------------------- BUILD -----------------------------//

Task("Build")
  .IsDependentOn("BuildClient")
  .IsDependentOn("BuildServer");

Task("BuildClient")
  .Does(() =>
  {
    Information("Building Client");
    StartPowershellFile("BuildClient.ps1", args => {
        args.Append("uprojectLocation", uprojectLocation);
        args.Append("outputDirectory", outputDirectory);
        args.Append("platform", clientPlatform);
    }); 
  });

Task("BuildServer")
  .Does(() =>
  {
    Information("Building Server");
    StartPowershellFile("BuildServer.ps1", args => {
        args.Append("uprojectLocation", uprojectLocation);
        args.Append("outputDirectory", outputDirectory);
        args.Append("platform", serverPlatform);
    }); 
  });

//---------------------------- PACKAGE ----------------------------//

Task("Package")
  .IsDependentOn("PackageClient")
  .IsDependentOn("PackageServer");

Task("PackageClient")
  .Does(() => {
    Zip("C:/IODist/WindowsNoEditor", "C:/IODist/WindowsNoEditor.zip");
  });

Task("PackageServer")
  .Does(() => {
    CopyFile("install.bat", "C:/IODist/WindowsServer/install.bat");
    CopyFile("UE4PrereqSetup_x64.exe", "C:/IODist/WindowsServer/UE4PrereqSetup_x64.exe");
    CopyFile("VC_redist.x64.exe", "C:/IODist/WindowsServer/VC_redist.x64.exe");
    Zip("C:/IODist/WindowsServer", "C:/IODist/WindowsServer.zip");
  });

//---------------------------- DEPLOY ----------------------------//

Task("Deploy")
  .IsDependentOn("DeployClient")
  .IsDependentOn("DeployServer");

Task("DeployClient")
  .Does(async(context) => {
    Information("Deploying Client");
    var settings = new UploadSettings()
      .SetAccessKey(awsAccessKey)
      .SetSecretKey(awsSecretKey)
      .SetBucketName(bucketName)
      .SetRegion(s3Region);  

    await S3Upload("C:/IODist/WindowsNoEditor.zip", "IOClient.zip", settings);
  });

Task("DeployServer")
  .Does(async(context) =>
  {
    Information("Deploying Server");
    var settings = new UploadSettings()
      .SetAccessKey(awsAccessKey)
      .SetSecretKey(awsSecretKey)
      .SetBucketName(bucketName)
      .SetRegion(s3Region);

    await S3Upload("C:/IODist/WindowsServer.zip", "IOServer.zip", settings);
  });

//----------------------------- START -----------------------------//

Task("All")
  .IsDependentOn("Build")
  .IsDependentOn("Package")
  .IsDependentOn("Deploy");

RunTarget(target);
//aws gamelift upload-build --name IO --build-version 0.6.0 --build-root C:\IODist\WindowsServer --operating-system WINDOWS_2012 --region us-east-2
//IO\Binaries\Win64\IOServer-Win64-Shipping.exe 
//port:7777 UDP 0.0.0.0/0
//aws gamelift create-game-session --maximum-player-session-count 10 --fleet-id fleet-5b1e2a03-5e36-4b77-9377-1bb07362fd96