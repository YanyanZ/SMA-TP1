jQuery.get('agent0.info', function(text)
      {
	  $('#agent1').val(text);
      },
      'text');