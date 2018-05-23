if ( !!~window.location.href.indexOf("/order-complete") ) {
	AddShoppersConversion = {
			order_id: document.querySelector('order-number').innerText.replace(/\D/g,''),
			value: document.querySelector('.order-total-qty.ng-binding').innerText
	};
}

var js = document.createElement('script'); js.type = 'text/javascript'; js.async = true; js.id = 'AddShoppers';

// Checkout Language Checking
if ( document.querySelector(".home-button") ) {
	if ( document.querySelector(".home-button").getAttribute('href') === "https://www.autodesk.com/products" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b6ffe694aa05ea29034e';
		console.log('USA');
	}
	else if ( document.querySelector(".home-button").getAttribute('href') === "https://www.autodesk.ca/en/products-standard" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b72ad55930062af5a974';
		console.log('CA');
	}
	else if ( document.querySelector(".home-button").getAttribute('href') === "https://www.autodesk.co.uk/products" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b75278f2f2ea9058224a';
		console.log('UK');
	}
	else if ( document.querySelector(".home-button").getAttribute('href') === "https://www.autodesk.de/products" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b718d559300630395abe';
		console.log('DE');
	}
	else {
		console.log('Element Changed / Unknown Country');
	}
}
else if ( document.querySelector(".grid-columns.small-12.medium-6.large-6 .img-responsive") ) {
	if ( document.querySelector(".grid-columns.small-12.medium-6.large-6 .img-responsive").getAttribute('src') === "//drh.img.digitalriver.com/DRHM/Storefront/Site/adskjp/cm/images/marvel/autodesk_estore_ja.png" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b79178f2f2eb949efc40';
		console.log('JP');
	}
	else {
		console.log('Element Changed / Unknown Country');
	}
}

// Rest of Site Language Checking
else if ( document.querySelector("a.geo-navigation-site-selector.wd-uppercase span") ) {
	if ( document.querySelector("a.geo-navigation-site-selector.wd-uppercase span").innerText.toLowerCase() === "united states" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b6ffe694aa05ea29034e';
		console.log('USA');
	}
	else if ( document.querySelector("a.geo-navigation-site-selector.wd-uppercase span").innerText.toLowerCase() === "canada - en" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b72ad55930062af5a974';
		console.log('CA');
	}
	else if ( document.querySelector("a.geo-navigation-site-selector.wd-uppercase span").innerText.toLowerCase() === "united kingdom (£)" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b75278f2f2ea9058224a';
		console.log('UK');
	}
	else if ( document.querySelector("a.geo-navigation-site-selector.wd-uppercase span").innerText.toLowerCase() === "dach" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b718d559300630395abe';
		console.log('DE');
	}
	else if ( document.querySelector("a.geo-navigation-site-selector.wd-uppercase span").innerText === "日本" ) {
		js.src = ('https:' == document.location.protocol ? 'https://shop.pe/widget/' : 'http://cdn.shop.pe/widget/') + 'widget_async.js#5a26b79178f2f2eb949efc40';
		console.log('JP');
	}
	else {
		console.log('Element Changed / Unknown Country');
	}
}

document.getElementsByTagName("head")[0].appendChild(js);