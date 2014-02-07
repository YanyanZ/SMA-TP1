jQuery.get('agent1.info', function(text)
      {
	  $('#agent2').val(text);
      },
      'text');