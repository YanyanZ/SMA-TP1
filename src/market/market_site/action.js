jQuery.get('market.action', function(text)
      {
	  $('#market').val(text);
      },
      'text');