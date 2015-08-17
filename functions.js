var color1url = "https://api.particle.io/v1/devices/53ff70066667574832462567/setColor1?access_token=3e0eff8995da2e99f3c0a46a62cfd2ee61cd5e18"
var color2url = "https://api.particle.io/v1/devices/53ff70066667574832462567/setColor2?access_token=3e0eff8995da2e99f3c0a46a62cfd2ee61cd5e18"
var color3url = "https://api.particle.io/v1/devices/53ff70066667574832462567/setColor3?access_token=3e0eff8995da2e99f3c0a46a62cfd2ee61cd5e18"
var color1 = undefined
var color2 = undefined
var color3 = undefined

$(document).ready(function () {
	$("#color1").on("change",color1Submit)
	$("#color2").on("change",color2Submit)
	$("#color3").on("change",color3Submit)
})

function ajaxRequest (color, url) {
	$.ajax({
		dataType: 'json',
		url: url,
		data: {'args': color},
		type: 'POST',
		success: function(data){
		}.bind(this),
		error: function(xhr, status, err) {
			alert("awww! I'm sooo sorry, but the request failed :'(")
		}
	});
}
function color1Submit(e) {
	var color = $('#color1').val()
	ajaxRequest(color, color1url)
	e.preventDefault()
}
function color2Submit(e) {
	var color = $('#color2').val()
	ajaxRequest(color, color2url)
	e.preventDefault()
}
function color3Submit(e) {
	var color = $('#color3').val()
	ajaxRequest(color, color3url)
	e.preventDefault()
}