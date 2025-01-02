$ErrorActionPreference = 'Stop';

$packageName= 'bex'
$version = "0.2"
$toolsDir   = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url        = "https://github.com/BetterException/bex/releases/download/$version/bex-win64.zip"
$hash = "91d66be97b643a402b89992f7ed2a4275f431315be9ff293cdf5e25f9768b7d9"

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = $hash
  checksumType  = 'SHA256'
}

Install-ChocolateyZipPackage @packageArgs