$ErrorActionPreference = 'Stop';

$packageName= 'bex'
$version = "0.2"
$toolsDir   = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url        = "https://github.com/BetterException/bex/releases/download/$version/bex-win64.zip"
$hash = "e45ed5be9a497d62249b0d8ef6429c3d824a9f9dc4a77e0e263ddcab3f57b9a6"

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = $hash
  checksumType  = 'SHA256'
}

Install-ChocolateyZipPackage @packageArgs