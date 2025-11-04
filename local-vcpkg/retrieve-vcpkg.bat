
if not exist vcpkg\.vcpkg-root ( git submodule init && git submodule update )

if exist vcpkg\NUL (
   cd vcpkg
   cmd /c .\bootstrap-vcpkg.bat
   .\vcpkg.exe upgrade --no-dry-run
   for %%t in (x64-windows x86-windows) do .\vcpkg.exe install --triplet %%t  opencv2
   cd ..  
)


