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
    # The path to the directory containing the header files to repair.
    [Parameter(Mandatory=$true,Position=0)]
    [string]$InputFileDir,

    # The path to the directory where the modified header files should go.
    [Parameter(Mandatory=$true,Position=1)]
    [string]$OutputFileDir
)

Get-ChildItem -Path $HeaderFileDirectory | Where-Object { $_.Extension -eq '.hpp' } | ForEach-Object {
  $newContents = @(
    "#ifdef DLL_EXPORTS",
    "#  define DLL_API __declspec(dllexport)",
    "#else",
    "#  define DLL_API __declspec(dllimport)",
    "#endif",
    ""
  )

  $newContents += Get-Content $_.FullName | ForEach-Object { $_ -replace "class $className", "class DLL_API $className" }

  $newFile = Join-Path -Path $OutputFileDir -ChildPath $_.Name
  Set-Content $newFile -Value $newContents
}
