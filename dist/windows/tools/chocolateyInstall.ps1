$ErrorActionPreference = 'Stop';

$packageName= 'bex'
$version = '0.1'
$toolsDir   = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url        = "https://github.com/BetterException/bex/releases/download/$version/bex-win64.zip"
$hash = 'ac80624dbb8712dd61117a3f28ddb7a1ede9ca17f98d30297a253ba760e17284'

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = $hash
  checksumType  = 'SHA256'
}

Install-ChocolateyZipPackage @packageArgs