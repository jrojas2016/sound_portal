var color1url = "https://api.particle.io/v1/devices/53ff70066667574832462567/setColor1?access_token=3e0eff8995da2e99f3c0a46a62cfd2ee61cd5e18"
var color2url = "https://api.particle.io/v1/devices/53ff70066667574832462567/setColor2?access_token=3e0eff8995da2e99f3c0a46a62cfd2ee61cd5e18"
var color3url = "https://api.particle.io/v1/devices/53ff70066667574832462567/setColor3?access_token=3e0eff8995da2e99f3c0a46a62cfd2ee61cd5e18"
var color1 = undefined
var color2 = undefined
var color3 = undefined

$(document).ready(function () {
	$("#color1").on("change",color1Submit)
})

function color1Submit(e) {
	console.log('lets see')
	var color = $('#color1').val()
	$.ajax({
		dataType: 'json',
		url: color1url,
		data: {'args': color},
		type: 'POST',
		success: function(data){
			color1 = color
		}.bind(this),
		error: function(xhr, status, err) {
			alert("awww! I'm sooo sorry, but the request failed :'(")
		}
	});
	e.preventDefault()
}