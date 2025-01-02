$ErrorActionPreference = 'Stop';

$packageName= 'bex'
$version = "0.2"
$toolsDir   = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url        = "https://github.com/BetterException/bex/releases/download/$version/bex-win64.zip"
$hash = "0f32cd9b0aff25a1c63310b16158e3213875391d6cfdc8e4d4e0f668820a82f5"

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = $hash
  checksumType  = 'SHA256'
}

Install-ChocolateyZipPackage @packageArgs