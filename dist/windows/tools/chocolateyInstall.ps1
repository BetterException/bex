$ErrorActionPreference = 'Stop';

$packageName= 'bex'
$version = "0.2"
$toolsDir   = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url        = "https://github.com/BetterException/bex/releases/download/$version/bex-win64.zip"
$hash = "cbdff213fe58f27066a6ab6a5fe8e38766aceac0b8c7be76ccb332e8d1c691c1"

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = $hash
  checksumType  = 'SHA256'
}

Install-ChocolateyZipPackage @packageArgs