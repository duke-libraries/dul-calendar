// Javascript for decro Tutorial module
(function($) {
	Drupal.behaviors.decro_tutorial = {
		attach : function(context, settings) {
			
			// the settings that were created in the 
			// page callback are accessible in this manner
			s = settings.decro_tutorial;
			
			// now, I'm going to add markup to the #decro-container DOM element
			// that was also created in the page callback
			
			$('#decro-container').html(
				'<div>' + 
				'The specified team ID was: ' + s.team_id + '<br />' +
				'The specified sport ID was: ' + s.team_sport + '<br />' +
				'Finally, the specified season was: ' + s.season +
				'</div>'
			);
		}
	}	
})(jQuery);
