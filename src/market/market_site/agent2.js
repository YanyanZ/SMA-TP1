jQuery.get('agent2.info', function(text)
      {
	  $('#agent3').val(text);
      },
      'text');