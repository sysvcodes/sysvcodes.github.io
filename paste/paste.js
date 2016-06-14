
/*
** By SysV
*/

$(document).ready(function(){
	
	$("body").css("background-color", "#333232");
	$("body").css("color", "#00ff80");
	
	var url = window.location.toString();
	if (url.indexOf("?name=") == -1) {
		alert("Invalid paste.");
		return false;
	}
	
	var splited = url.split("?name=");
	var param = splited[1];
	
	if (!(param[param.length-1] == 's' && param[param.length-2] == '.')) {
		alert("Invalid paste.");
		return false;
	}
	
	$.get(param, function(data){
		var content = data;
		
		content = content.replace(/\/\//g, "||");
		content = content.replace(/\t/g, "    ");
		content = content.replace(/([;#><,.*+?^=!:${}()\[\]\/&])/g, 
			"<font style='color:#00FFFF;font-weight:bold;'>$1</font>");
		content = content.replace(/def/g, "<font style='color:#FF80C0;font-weight:bold;'>def</font>");
		content = content.replace(/req/g, "<font style='color:#FF80C0;font-weight:bold;'>req</font>");
		content = content.replace(/\tret /g, "<font style='color:#00FFFF;font-weight:bold;'>ret </font>");
		content = content.replace(/\tret\t/g, "<font style='color:#00FFFF;font-weight:bold;'>ret </font>");
		content = content.replace(/ ret\t/g, "<font style='color:#00FFFF;font-weight:bold;'>ret </font>");
		content = content.replace(/ ret /g, "<font style='color:#00FFFF;font-weight:bold;'> ret </font>");
		content = content.replace(/\tdo /g, "<font style='color:#00FFFF;font-weight:bold;'>do </font>");
		content = content.replace(/\tdo\t/g, "<font style='color:#00FFFF;font-weight:bold;'>do </font>");
		content = content.replace(/ do\t/g, "<font style='color:#00FFFF;font-weight:bold;'> do </font>");
		content = content.replace(/ do /g, "<font style='color:#00FFFF;font-weight:bold;'> do </font>");
		content = content.replace(/\tfor /g, "<font style='color:#00FFFF;font-weight:bold;'>for </font>");
		content = content.replace(/\tfor\t/g, "<font style='color:#00FFFF;font-weight:bold;'>for </font>");
		content = content.replace(/ for\t/g, "<font style='color:#00FFFF;font-weight:bold;'> for </font>");
		content = content.replace(/ for /g, "<font style='color:#00FFFF;font-weight:bold;'> for </font>");
		content = content.replace(/\tif /g, "<font style='color:#00FFFF;font-weight:bold;'>if </font>");
		content = content.replace(/\tif\t/g, "<font style='color:#00FFFF;font-weight:bold;'>if </font>");
		content = content.replace(/ if\t/g, "<font style='color:#00FFFF;font-weight:bold;'> if </font>");
		content = content.replace(/ if /g, "<font style='color:#00FFFF;font-weight:bold;'> if </font>");
		content = content.replace(/\telif /g, "<font style='color:#00FFFF;font-weight:bold;'>elif </font>");
		content = content.replace(/\telif\t/g, "<font style='color:#00FFFF;font-weight:bold;'>elif </font>");
		content = content.replace(/ elif\t/g, "<font style='color:#00FFFF;font-weight:bold;'> elif </font>");
		content = content.replace(/ elif /g, "<font style='color:#00FFFF;font-weight:bold;'> elif </font>");
		content = content.replace(/\tbreak /g, "<font style='color:#00FFFF;font-weight:bold;'>break </font>");
		content = content.replace(/\tbreak\t/g, "<font style='color:#00FFFF;font-weight:bold;'>break </font>");
		content = content.replace(/ break\t/g, "<font style='color:#00FFFF;font-weight:bold;'> break </font>");
		content = content.replace(/ break /g, "<font style='color:#00FFFF;font-weight:bold;'> break </font>");
		content = content.replace(/\tcontinue /g, "<font style='color:#00FFFF;font-weight:bold;'>continue </font>");
		content = content.replace(/\tcontinue\t/g, "<font style='color:#00FFFF;font-weight:bold;'>continue </font>");
		content = content.replace(/ continue\t/g, "<font style='color:#00FFFF;font-weight:bold;'> continue </font>");
		content = content.replace(/ continue /g, "<font style='color:#00FFFF;font-weight:bold;'> continue </font>");
		
		// Processa comentários e strings.
		content = content.replace(/\n\n/g, "\n<NLNL>");
		content = content.replace(/\r\n\r\n/g, "\n<NLNL>");
		
		var splited = content.split(/\n/);
		var finalSource = "";
		var lineCounter = 1;
		for (var a=0; a<splited.length; a++) {
			if (splited[a]) {
				var line = splited[a];
				var lineTemp = ""+ lineCounter +"";
				
				if (lineTemp.length == 1) {
					lineTemp = "&nbsp;&nbsp;0"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				} else if (lineTemp.length == 2) {
					lineTemp = "&nbsp;&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				} else if (lineTemp.length == 3) {
					lineTemp = "&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				} else if (lineTemp.length == 4) {
					lineTemp = ""+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				var lineContent = "<font style='color:gray;'>"+ lineTemp +"</font>";
				
				if (line.indexOf("||") != -1) {
					var s1 = line.split("||");
					var p2 = s1[1].replace(/color:/g, "");
					var p2 = p2.replace(/font-weight:/g, "");
					finalSource += lineContent + s1[0] + "<font style='color:#bfbfbf;font-style:italic;'>//" + p2 +"</font>"+ "<br>";
				} else if (line.indexOf("\"") != -1) {
					var s1 = line.split("\"");
					var p2 = s1[1].replace(/color:/g, "");
					var p2 = p2.replace(/font-weight:/g, "");
					var b_flag = false;
					var c_flag = false;
					finalSource += lineContent;
					
					for (var b=0; b<s1.length; b++) {
						if (b_flag == true) {
							b_flag = false;
							console.log(s1[b]);
							finalSource += "<font style='color:#00FF00;'>\"" + s1[b] +"\"</font>";
							
							//finalSource = finalSource.replace(/<NLNL>/g, "<br>");
							// --
							// var lineCounterB = lineCounter + 1;
							// var lineTempB = ""+ lineCounterB +"";
							// if (lineTempB.length == 1) {
								// lineTempB = "&nbsp;&nbsp;0"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
							// } else if (lineTempB.length == 2) {
								// lineTempB = "&nbsp;&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
							// } else if (lineTempB.length == 3) {
								// lineTempB = "&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
							// } else if (lineTempB.length == 4) {
								// lineTempB = ""+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
							// }
							// lineContent = "<font style='color:gray;'>"+ lineTempB +"</font>";
							if (finalSource.indexOf("<NLNL>") != -1) {
								c_flag = true;
							}
							// --
							
						} else if (b_flag == false) {
							b_flag = true;
							finalSource += s1[b];
						}
					}
					if (c_flag == false) {
						finalSource += "<br>";
					} else {
						c_flag = false;
						var lineCounterB = lineCounter + 1;
						var lineTempB = ""+ lineCounterB +"";
						if (lineTempB.length == 1) {
							lineTempB = "&nbsp;&nbsp;0"+ lineCounterB +"&nbsp;&nbsp;&nbsp;&nbsp;";
						} else if (lineTempB.length == 2) {
							lineTempB = "&nbsp;&nbsp;"+ lineCounterB +"&nbsp;&nbsp;&nbsp;&nbsp;";
						} else if (lineTempB.length == 3) {
							lineTempB = "&nbsp;"+ lineCounterB +"&nbsp;&nbsp;&nbsp;&nbsp;";
						} else if (lineTempB.length == 4) {
							lineTempB = ""+ lineCounterB +"&nbsp;&nbsp;&nbsp;&nbsp;";
						}
						lineContent = "<font style='color:gray;'>"+ lineTempB +"</font>";
						finalSource += "<br>"+ lineContent +"<br>";
						lineCounter++;
					}
				} else
					finalSource += lineContent + splited[a] +"<br>";
				lineCounter++;
			}
		}
		
		//finalSource = finalSource.replace(/<NLNL>/g, "<br><br>");
		
		$("#content").html(finalSource);
	});
});
