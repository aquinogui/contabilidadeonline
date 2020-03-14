// MAPA -------------------------

	var map;
	
	function initialize() {
		var myLatlng = new google.maps.LatLng(-23.551502, -46.554058);

		var contentString = '<div style="text-align:center;">'+
			'<p>Rua Antonio de Barros, 2.391 Cj 42<br/>Tatuapé - São Paulo - CEP 03401-001</p>'+
			'</div>';
		
		var mapOptions = {
				zoom: 14,
				center: myLatlng,
				scrollwheel: false,
			};
		
		
		map = new google.maps.Map(document.getElementById('contato-map'), mapOptions);
		
		var marker = new google.maps.Marker({
				position: myLatlng,
				map: map,
				title: 'KDI Treinamentos'
			});
		
		var infowindow = new google.maps.InfoWindow({
			content: contentString
		});
		
		google.maps.event.addListener(marker, 'click', function() {
			infowindow.open(map,marker);
		});
	}

	google.maps.event.addDomListener(window, 'load', initialize);
// MAPA -------------------------/
