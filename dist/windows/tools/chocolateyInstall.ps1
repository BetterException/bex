$ErrorActionPreference = 'Stop';

$packageName= 'bex'
$version = "0.2"
$toolsDir   = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url        = "https://github.com/BetterException/bex/releases/download/$version/bex-win64.zip"
$hash = "64358e3ea77709893e887034bd0b1c3a3069996182b2a40d00f7fc4562667396"

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = $hash
  checksumType  = 'SHA256'
}

Install-ChocolateyZipPackage @packageArgs