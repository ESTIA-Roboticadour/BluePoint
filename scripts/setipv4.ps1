# PowerShell script to change IPv4 settings interactively
# Must be run as Administrator

function Set-IPv4Static {
    param (
        [string]$InterfaceAlias,
        [string]$IPAddress,
        [string]$SubnetPrefixLength
    )

    # Remove existing IPv4 addresses
    Get-NetIPAddress -InterfaceAlias $InterfaceAlias -AddressFamily IPv4 -ErrorAction SilentlyContinue | Remove-NetIPAddress -Confirm:$false

    # Add static IP address
    $Gateway = ($IPAddress -replace '\d+$', '1')
    New-NetIPAddress -InterfaceAlias $InterfaceAlias -IPAddress $IPAddress -PrefixLength $SubnetPrefixLength -DefaultGateway $Gateway
}

function Set-IPv4DHCP {
    param (
        [string]$InterfaceAlias
    )

    # Enable DHCP for IP and DNS
    Set-NetIPInterface -InterfaceAlias $InterfaceAlias -Dhcp Enabled
    Set-DnsClientServerAddress -InterfaceAlias $InterfaceAlias -ResetServerAddresses
}

# List active network interfaces
$interfaces = Get-NetAdapter | Where-Object { $_.Status -eq "Up" }

Write-Host ""
Write-Host "Available network interfaces:"
$interfaces | ForEach-Object { Write-Host "$($_.InterfaceIndex)) $($_.Name)" }

$choice = Read-Host "`nEnter the interface index to configure"
$interface = $interfaces | Where-Object { $_.InterfaceIndex -eq [int]$choice }

if (-not $interface) {
    Write-Host "Error: Network interface not found."
    exit
}

# Main menu
Write-Host ""
Write-Host "Choose the IP configuration:"
Write-Host "1) Static IP: 172.31.1.100 / 255.255.0.0"
Write-Host "2) Static IP: 172.31.2.100 / 255.255.0.0"
Write-Host "3) DHCP (automatic)"

$ipChoice = Read-Host "`nYour choice (1/2/3)"

switch ($ipChoice) {
    "1" {
        Set-IPv4Static -InterfaceAlias $interface.Name -IPAddress "172.31.1.100" -SubnetPrefixLength 16
        Write-Host "IP set to 172.31.1.100 /16"
    }
    "2" {
        Set-IPv4Static -InterfaceAlias $interface.Name -IPAddress "172.31.2.100" -SubnetPrefixLength 16
        Write-Host "IP set to 172.31.2.100 /16"
    }
    "3" {
        Set-IPv4DHCP -InterfaceAlias $interface.Name
        Write-Host "IP set to DHCP"
    }
    default {
        Write-Host "Invalid choice."
    }
}
