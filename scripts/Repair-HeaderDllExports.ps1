<#
.Synopsis
   Adds missing DLL Exports to C++ header files.
.DESCRIPTION
   Fixes Wrapture-generated header files so that they have the correct export
   decorations added to declarations.
.EXAMPLE
   Example of how to use this cmdlet
.EXAMPLE
   Another example of how to use this cmdlet
#>

[CmdletBinding()]

Param (
    # An array of paths to the files to repair.
    [Parameter(Mandatory=$true,Position=0)]
    [string[]]$HeaderFilePaths
)

$HeaderFilePaths | ForEach-Object {
  $className = [System.IO.Path]::GetFileNameWithoutExtension($_)
  $newContents = Get-Content $_ | `
    ForEach-Object { $_ -replace "class $className", "class DLL_API $className" }
  $preambleLines = @(
    "#ifdef DLL_EXPORTS",
    "#  define DLL_API __declspec(dllexport)",
    "#else",
    "#  define DLL_API __declspec(dllimport)",
    "#endif",
    ""
  )
  Set-Content $_ -Value ($preambleLines + $newContents)
}
