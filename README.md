## Getting Started
The first thing to install would be the [Epic Games Launcher](https://store.epicgames.com/en-US/download)

This project uses functionality that is only accessible when you build the engine from source code: [Checkout branch 4.21 of Unreal Engine](https://github.com/EpicGames/UnrealEngine/tree/4.21)
_* Here is a guide on [Downloading Unreal Engine Source Code](https://dev.epicgames.com/documentation/en-us/unreal-engine/downloading-unreal-engine-source-code)_

While that is downloading and installing you will also need to download [Visual Studio 2017](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false). 
_* I have see people get VS Code to work but I have no idea how to do that._

## Build and Deployment
This project uses [Cake Build](https://cakebuild.net/) to automate the building and deploying of the client and server


## Hosting and Infrastructure
This project was setup to use AWS Gamelist to host and manage the game sessions

##### Upload a New Build Image
`aws gamelift upload-build --name IO --build-version <your build number> --build-root C:\IODist\WindowsServer --operating-system WINDOWS_2012 --region us-east-2`

##### Create new session
`aws gamelift create-game-session --maximum-player-session-count 10 --fleet-id fleet-7e5b6ece-7d06-4ff5-aebd-2308df9e700f`