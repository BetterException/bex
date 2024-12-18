## Files to touch before release

- `CMakeLists.txt`
- `snapcraft.yaml`
- `dist/windows/bex.nuspec`
- `dist/windows/tools/chocolateyInstall.ps1`

## External files to touch after release

- [`homebrew-bex/bex.rb`](https://github.com/BetterException/homebrew-bex/blob/main/bex.rb)

## Tasks to perform on release

- Build and create the release through API endpoint on a Windows machine, sorting the Choco release
- In the second pipeline, trigger the remote build for the Snap release
- In the second pipeline, download the sources' tar.gz file and compute the SHA256 for updating the homebrew file
- Update the [`homebrew-bex/bex.rb`](https://github.com/BetterException/homebrew-bex/blob/main/bex.rb) and `chocolateyInstall.ps1` file with the updated hash

## Triggering the release

- Create a tag locally (e.g. `v1.2.3`)
- Push the tag to GitHub (via. `git push origin v1.2.3`)
