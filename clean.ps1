# Set-ExecutionPolicy RemoteSigned
Get-ChildItem -Path .\*.obj -Recurse | ForEach-Object { Remove-Item $_.FullName }
Get-ChildItem -Path .\*.exe -Recurse | ForEach-Object { Remove-Item $_.FullName }
Get-ChildItem -Path .\*.pdb -Recurse | ForEach-Object { Remove-Item $_.FullName }
Get-ChildItem -Path .\*.ilk -Recurse | ForEach-Object { Remove-Item $_.FullName }