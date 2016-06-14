
/*
** By SysV
*/

$(document).ready(function(){

	$("body").css("background-color", "#333232");
	$("body").css("color", "#00ff80");
	
	$("#gobtn").on("click", function(){
		window.location.href = "?f="+ $("#filename").val();
	});
	$("#filename").keypress(function(e){
		var tecla = (e.keyCode?e.keyCode:e.which);
		if (tecla == 13){
			window.location.href = "?f="+ $("#filename").val();
		}
	});
	
	var url = window.location.toString();
	if (url.indexOf("?f=") != -1) {
		var splited = url.split("?f=");
		var param = splited[1];
		if (!(param[param.length-1] == 's' && param[param.length-2] == '.')) {
			$("#content").css("visibility", "visible");
			$("#filename").val("");
			$("#filename").focus();
			alert("Invalid paste.");
			return false;
		} else {
			loadFile(param);
		}
	} else {
		$("#content").css("visibility", "visible");
		$("#filename").val("");
		$("#filename").focus();
		return false;
	}
});
	
function loadFile(param){
	$.get(param, function(data){
		var content = data;
		
		content = content.replace(/\/\//g, "||");
		content = content.replace(/\t/g, "    ");
		content = content.replace(/([;#><,+?^=!:${}()\[\]&])/g, 
			"<font style='color:#00FFFF;font-weight:bold;'>$1</font>");
		content = content.replace(/\/\*/g, "<font style='color:#bfbfbf;font-style:italic;'>/*");
		content = content.replace(/\*\//g, "*/</font>");
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
		content = content.replace(/\n/g, "\t\n");
		
		var splited = content.split(/\n/);
		var finalSource = "";
		var lineCounter = 1;
		for (var a=0; a<splited.length; a++) {
			if (splited[a]) {
				var line = splited[a];
				var lineTemp = ""+ lineCounter +"";
				
				if (lineTemp.length == 1) 
					lineTemp = "&nbsp;&nbsp;0"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				else if (lineTemp.length == 2) 
					lineTemp = "&nbsp;&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				else if (lineTemp.length == 3) 
					lineTemp = "&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
				else if (lineTemp.length == 4) 
					lineTemp = ""+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
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
							finalSource += "<font style='color:#00FF00;'>\"" + s1[b] +"\"</font>";
						} else if (b_flag == false) {
							b_flag = true;
							finalSource += s1[b];
						}
					}
					finalSource += "<br>";
				} else
					finalSource += lineContent + splited[a] +"<br>";
				lineCounter++;
			}
		}
		
		lineTemp = ""+ lineCounterB +"";
		if (lineTemp.length == 1) 
			lineTemp = "&nbsp;&nbsp;0"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
		else if (lineTemp.length == 2) 
			lineTemp = "&nbsp;&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
		else if (lineTemp.length == 3) 
			lineTemp = "&nbsp;"+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
		else if (lineTemp.length == 4) 
			lineTemp = ""+ lineCounter +"&nbsp;&nbsp;&nbsp;&nbsp;";
		lineContent = "<font style='color:gray;'>"+ lineTemp +"</font>";
		finalSource += lineContent +"<br>";
		document.title = "SPL - "+ lineCounter + " lines!";
		
		$("#content").html(finalSource);
		$("#content").css("visibility", "visible");
	});
};
