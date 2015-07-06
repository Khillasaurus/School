//////////// MISCELLANEOUS ////////////

function open_panel(no, item){
  [ $('box_nav_1'), $('box_nav_2'), $('box_nav_3'), $('box_nav_4'), $('box_nav_5') ].each(function(s) { s.removeClassName('open'); });
  [ $('box_content_1'), $('box_content_2'), $('box_content_3'), $('box_content_4'), $('box_content_5') ].each(function(s) { s.hide(); });
  $('box_nav_' + no).addClassName('open');
  $('box_content_' + no).style.display = 'block';
  item.blur();
}

function open_tab(elem, tab){
  var lis = $('tab_titles').getElementsByTagName("li");
  for (var i = 0; i < lis.length; i++) {
      lis[i].className=lis[i].className.replace(new RegExp(" active\\b"), "");
  }
  elem.blur();
  var tabs = $('tabs_holder').getElementsByClassName("table_tab");
  for (var i = 0; i < tabs.length; i++) {
      tabs[i].hide();
  }
  $(tab).show();
  $(tab+'_title').className+=' active';
  return false;
}

function toggle_settings(trigger, wrapper){
  var labels = $(wrapper).getElementsByTagName("label");
  var inputs = $(wrapper).getElementsByTagName("input");
  stat = $(trigger);
  if (stat.checked) {
    Element.show(wrapper)
    for (var i = 0; i < labels.length; i++) { labels[i].className = "" };
    for (var i = 0; i < inputs.length; i++) { inputs[i].removeAttribute('disabled'); };
  }
  else {
    Element.hide(wrapper)
    for (var i = 0; i < labels.length; i++) { labels[i].className = "disabled_label" };
    for (var i = 0; i < inputs.length; i++) { inputs[i].disabled = "disabled" };
  };
}

function flash_container(container){
  container = 'div.'+container;
  $$(container).invoke('hide');
  $$(container).each(function(s) {
    Effect.SlideDown(s);
  });
}

function get_selection()
{
  var txt = null;
  if (window.getSelection)
    txt = window.getSelection();
  else if (document.getSelection)
    txt = document.getSelection();
  else if (document.selection)
    txt = document.selection.createRange().text;
  return txt == '' ? null : txt;
}

function selectElementText(id)
{
  var el = $(id);
  if (document.selection)
  {
    var range = document.body.createTextRange();
    range.moveToElementText(el);
    range.select();
  }
  else if (window.getSelection)
  {
    var range = document.createRange();
    range.selectNode(el);
    window.getSelection().addRange(range);
  }
}

// This code based on the code written by "sticks" at
// http://lyncd.com/2009/03/better-google-analytics-javascript/
// insert Google Analytics script
function insertGA(tracker_id)
{

  var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www."), pageTracker, s;
  s = document.createElement('script');
  s.src = gaJsHost + 'google-analytics.com/ga.js';
  s.type = 'text/javascript';
  s.onloadDone = false;
  function init ()
  {
    pageTracker = _gat._getTracker(tracker_id);
    pageTracker._trackPageview();
  }
  s.onload = function ()
  {
    s.onloadDone = true;
    init();
  };
  s.onreadystatechange = function()
  {
    if (('loaded' === s.readyState || 'complete' === s.readyState) && !s.onloadDone) {
      s.onloadDone = true;
      init();
    }
  };
  document.getElementsByTagName('head')[0].appendChild(s);
}

function delayLoadGA(tracker_id)
{
  if (window.addEventListener)
    window.addEventListener('load', function(event) { insertGA(tracker_id); }, false);
  else if (window.attachEvent)
    window.attachEvent('onload', function(event) { insertGA(tracker_id); });
  else
    window.onload = function () { insertGA(tracker_id); };
}

function asyncInsertScript(id, src)
{
  if (document.getElementById(id)) return;
  var fjs = document.getElementsByTagName('script')[0];
  var js = document.createElement('script');
  js.id = id;
  js.type = 'text/javascript';
  js.async = true;
  js.src = src;
  fjs.parentNode.insertBefore(js, fjs);
}

//////////// BILLING ////////////

function payment_method_select(name, is_cc, payment_providers)
{
  if (name == '' || name == 'promotion')
  {
    for (var i=0; i<payment_providers.length; i++)
      $('pay_method_' + payment_providers[i]['name']).checked = false;
  }
  else
  {
    if (!$('pay_method_' + name).checked) $('pay_method_' + name).checked = true;

    if (is_cc)
    {
      if (!$('billing_info_panel').visible()) $('billing_info_panel').blindDown();
    }
    else
    {
      if ($('billing_info_panel').visible()) $('billing_info_panel').hide();
    }

    $('credit_card_card_type_image').src = '/images/payment_' + name + '.png';

    var already_cc = false;
    for (var i=0; i<payment_providers.length; i++)
    {
      var pp = payment_providers[i];
      var ppn = pp['cc'] ? 'cc' : pp['name'];

      $('pay_method_' + pp['name'] + '_div').className = (pp['name'] == name ? 'payment_method_selected' : 'payment_method') + (pp['name'] == 'amex' ? ' payment_method_amex' : '');
      if (already_cc && pp['cc']) continue;

      if (ppn == name || (pp['cc'] && is_cc))
        $('submit_button_' + ppn).show();
      else
        $('submit_button_' + ppn).hide();

      if (pp['cc']) already_cc = true
    }
  }
}

// on the prepay screen, after the user enters the number of months to prepay for, this will calculate
// the total amount they will be billed
function prepay_calc(txt)
{
  var num_months = parseInt(txt.value), total_val = 0;
  if (num_months + '' == txt.value)
  {
    subtotal_val = (prepay_base_price + prepay_storage_price) * num_months;
    total_val = subtotal_val && subtotal_val > 0 ? (subtotal_val + prepay_outstanding_balance) : 0;
    txt.style.background = '';
  }
  else
    txt.value = '0';

  $('prepay_total_span_2').innerHTML = $('prepay_total_span_1').innerHTML = $('prepay_total').value = total_val + '';
}

//////////// SLIDESHOW ////////////

/*** REQUIRES jQuery (and not Prototype) ***/

var slides_animating_direction = false, slide_auto_rotate_interval_obj = false, current_slide = 2;

function reset_slides_auto_rotate(direction, interval, width, list)
{
  if (slide_auto_rotate_interval_obj) {
    clearInterval(slide_auto_rotate_interval_obj);
    slide_auto_rotate_interval_obj = false;
  }
  slide_auto_rotate_interval_obj = setInterval(function(d, w, l) { rotate_slides(d, w, l); }, interval, direction, width, list);
}

function rotate_slides(direction, width, list)
{
  if (slides_animating_direction != false) return;
  current_slide += (direction == 'right' ? 1 : -1);
  if (current_slide == -1) current_slide = list.length - 1; else if (current_slide == list.length) current_slide = 0;
  slides_animating_direction = direction;
  $("#slideshow-label").delay(200).fadeOut(300, function() { $("#slideshow-label").text(list[current_slide][1]); }).fadeIn(300);
  $("#slideshow-wrapper").animate({ scrollLeft: direction == 'right' ? width * 2 : 0 }, 1000, 'jswing', function() {
    var slide = $('#slideshow-content div:' + (slides_animating_direction == 'right' ? 'nth-child(2)' : 'last-child')).detach();
    if (slides_animating_direction == 'right')
      $('#slideshow-content').append(slide);
    else
      $('#slideshow-content div:first-child').after(slide);
    $("#slideshow-wrapper").scrollLeft(width);
    slides_animating_direction = false;
  });
}

//////////// CATEGORY SETTINGS ////////////

function category_setting_toggle(type, enable)
{
  if (type == "backups")
	{
		var fields = ['backup_frequency_manually', 'backup_frequency_daily', 'backup_frequency_weekly', 'backup_frequency_monthly', 'settings_aws_send_backup'];
		var sections = ['aws_backups'];
		var section_fields = ['settings_aws_access_key_id', 'settings_aws_secret_access_key', 'settings_aws_s3_bucket'];

		if (enable)
		{
		  for (var i=0; i<fields.length; i++) $(fields[i]).disabled = false;
		}
		else
		{
      $('backup_frequency_manually').checked = true;
      $('settings_aws_send_backup').checked = false;

      for (var i = 0; i < fields.length; i++) $(fields[i]).disabled = true;
      for (var i = 0; i < sections.length; i++) $(sections[i]).hide();
      for (var i = 0; i < section_fields.length; i++) $(section_fields[i]).value = '';
		}
	}
	else if (type == 'notifications')
	{
    var fields = [
      'settings_trac_notification_use_public_cc', 'settings_notification_twitter_send', 'settings_notification_twitter_information_authorize', 'settings_notification_campfire_send',
			'settings_notification_basecamp_send', 'settings_notification_cia_send', 'settings_notification_customcallback_get_send', 'settings_notification_customcallback_send'
    ];
    var sections = ['notification_twitter', 'notification_campfire', 'notification_basecamp', 'notification_cia', 'notification_customcallback_get', 'notification_customcallback'];
		var section_fields = [
		  'settings_notification_campfire_information_subdomain',
			'settings_notification_campfire_information_user', 'settings_notification_campfire_information_password', 'settings_notification_campfire_information_room',
			'settings_notification_basecamp_information_subdomain', 'settings_notification_basecamp_information_user', 'settings_notification_basecamp_information_password',
			'settings_notification_basecamp_information_project', 'settings_notification_basecamp_information_category', 'settings_notification_cia_information_project',
      'settings_notification_customcallback_get_information_url', 'settings_notification_customcallback_get_information_user', 'settings_notification_customcallback_get_information_password',
			'settings_notification_customcallback_information_url', 'settings_notification_customcallback_information_user', 'settings_notification_customcallback_information_password'
		];

		if (enable)
		{
      for (var i=0; i<fields.length; i++) $(fields[i]).disabled = false;
		}
		else
		{
      for (var i = 0; i < fields.length; i++)
			{
        $(fields[i]).disabled = true;
        $(fields[i]).checked = false;
	    }
			for (var i = 0; i < sections.length; i++) $(sections[i]).hide();
      for (var i = 0; i < section_fields.length; i++) $(section_fields[i]).value = '';
		}
	}
}

//////////// NOTIFICATIONS ////////////

function notify_toggle_highlight(id, on_or_off)
{
  var row = $('notification_' + id + '_row'), cn = 'highlight';
  if (on_or_off != 'on' && (on_or_off == 'off' || row.hasClassName(cn)))
    row.removeClassName(cn);
  else
    row.addClassName(cn);
}

function notify_checkbox_all_click(id)
{
	var is_checked = $('projects_' + id + '_notify_all_tickets').checked;
	var c_comp = $('projects_' + id + '_notify_component_tickets'), c_own = $('projects_' + id + '_notify_owned_tickets'), c_report = $('projects_' + id + '_notify_reported_tickets'), c_update = $('projects_' + id + '_notify_updated_tickets');

  c_comp.disabled = is_checked;
  c_own.disabled = is_checked;
  c_report.disabled = is_checked;
  c_update.disabled = is_checked;

  if (is_checked)
	{
		c_comp.checked = true;
		c_own.checked = true;
		c_report.checked = true;
		c_update.checked = true;
	}
}

//////////// PERMISSIONS ////////////

function perm_toggle_highlight(prefix, id, on_or_off)
{
	var e = $('permission_' + prefix + '_' + id + '_row'), cn = 'highlight';
	if (on_or_off != 'on' && (on_or_off == 'off' || e.hasClassName(cn)))
	  e.removeClassName(cn);
  else
		e.addClassName(cn);

	if (prefix == 'category' || prefix == 'group')
	{
		// highlight the entire section
		var items = permission_section_map[id] || [];
		for (var i=0; i<items.length; i++)
		{
			var e2 = $('permission_' + (prefix == 'category' ? 'project' : 'user') + '_' + items[i] + '_row'), cn2 = 'highlight_light';
			if (on_or_off != 'on' && (on_or_off == 'off' || e2.hasClassName(cn2)))
		    e2.removeClassName(cn2);
		  else
		    e2.addClassName(cn2);
		}
	}
}

function permission_toggle_group(prefix, id)
{
	var expander = $('permission_' + prefix + '_' + id + '_expander');
  var items = permission_section_map[id] || [];
	var item_prefix = (prefix == 'category' ? 'project' : 'user');
	var vis = items.length > 0 ? $('permission_' + item_prefix + '_' + items[0] + '_row').visible() : false;
	for (var i=0; i<items.length; i++)
	{
	  var item = $('permission_' + item_prefix + '_' + items[i] + '_row');
		if (vis) item.hide(); else item.show();
	}
	expander.src = vis ? "/images/folder_tree_branch_collapsed_icon.gif" : "/images/folder_tree_branch_expanded_icon.gif";
}

function perm_toggle_row_enabled(prefix, id, skip_trac_permissions)
{
  var irepo = $('permission_' + prefix + '_' + id + '_repository'), iwebdav = $('permission_' + prefix + '_' + id + '_webdav');
  if ($('permission_' + prefix + '_' + id + '_project_admin').checked)
	{
  	irepo.selectedIndex = irepo.length-1;
  	irepo.disabled = true;
		if (!irepo.hasClassName('disabled')) irepo.addClassName('disabled');
  	iwebdav.selectedIndex = iwebdav.length-1;
  	iwebdav.disabled = true;
    if (!iwebdav.hasClassName('disabled')) iwebdav.addClassName('disabled');

    // add the relevant trac perms
    var project_id = prefix == 'project' ? id : (permission_parent_type == 'project' ? permission_parent_id : null);
		var user_id = prefix == 'user' ? id : (permission_parent_type == 'user' ? permission_parent_id : null);
		if (!skip_trac_permissions && project_id && user_id && permission_admin_user_ids.indexOf(user_id) < 0)
		{
			var trac_perms = permission_empty_repo_ids.indexOf(parseInt(project_id)) >= 0 ? permission_empty_repo_trac_perms : permission_repo_trac_perms;
			permission_update_trac_perms(prefix, id, 'add', trac_perms);
		}
  }
	else
	{
    var parent_type = null, parent_id = null;
		if (prefix == 'project' || prefix == 'user')
		{
		  parent_type = prefix == 'project' ? 'category' : 'group';
      for (s in permission_section_map) { if (permission_section_map[s].indexOf(parseInt(id)) >= 0) parent_id = s; }
	  }

		var disable_repo = true, disable_webdav = true;
		if (parent_type && parent_id)
		{
			var prepo = $('permission_' + parent_type + '_' + parent_id + '_repository'), pwebdav = $('permission_' + parent_type + '_' + parent_id + '_webdav');
      if ($F(prepo.id) == 'commit')
        disable_repo = false;
      if ($F(pwebdav.id) == 'write')
        disable_webdav = false;
		}

		if (disable_repo && !permission_force_disabled[prefix + '_' + id + '_repository'])
		{
		  irepo.disabled = false;
      if (irepo.hasClassName('disabled')) irepo.removeClassName('disabled');
	  }
    if (disable_webdav && !permission_force_disabled[prefix + '_' + id + '_webdav'])
		{
		  iwebdav.disabled = false;
      if (iwebdav.hasClassName('disabled')) iwebdav.removeClassName('disabled');
	  }
	}

	// add/remove the TRAC_ADMIN value
	if (!skip_trac_permissions)
	 permission_update_trac_perms(prefix, id, $('permission_' + prefix + '_' + id + '_project_admin').checked ? 'add' : 'remove', [permission_trac_perm]);
}

function perm_check_for_inheritance(prefix, id, perm, skip_trac_permissions)
{
  if (prefix != 'category' && prefix != 'group') return;

	var sele = $('permission_' + prefix + '_' + id + '_' + perm);
	var items = permission_section_map[id] || [];
  for (var i = 0; i < items.length; i++)
	{
		var item_type = prefix == 'category' ? 'project' : 'user', item_id = items[i];
		var iele = $('permission_' + item_type + '_' + item_id + '_' + perm);
		var disable_iele = false;
		if (perm == 'project_admin')
		{
		  if (sele.checked)
			{
	       if (!iele.checked)
				 {
		 	     iele.checked = true;
		 	     perm_toggle_row_enabled(item_type, item_id, skip_trac_permissions);
		     }
				 iele.disabled = true;
			}
			else
			{
				if (permission_admin_user_ids.indexOf(item_id) < 0 && !permission_force_disabled[item_type + '_' + item_id + '_project_admin'])
				  iele.disabled = false;
			}
		}
		else if (perm == 'repository')
		{
			if ($F(sele.id) == 'commit' || ($F(sele.id) == 'read' && $F(iele.id) == 'none'))
			{
	  	  iele.selectedIndex = ($F(sele.id) == 'commit' ? iele.length - 1 : iele.length - 2);

		    // add the relevant trac perms
		    var project_id = item_type == 'project' ? item_id : (permission_parent_type == 'project' ? permission_parent_id : null);
		    var user_id = item_type == 'user' ? item_id : (permission_parent_type == 'user' ? permission_parent_id : null);
		    if (!skip_trac_permissions && project_id && user_id && permission_admin_user_ids.indexOf(user_id) < 0)
		    {
		      var trac_perms = permission_empty_repo_ids.indexOf(project_id) >= 0 ? permission_empty_repo_trac_perms : permission_repo_trac_perms;
		      permission_update_trac_perms(item_type, item_id, 'add', trac_perms);
		    }
	    }
		}
		else if (perm == 'webdav')
		{
      if ($F(sele.id) == 'write' || ($F(sele.id) == 'read' && $F(iele.id) == 'none'))
	  	  iele.selectedIndex = ($F(sele.id) == 'write' ? iele.length-1 : iele.length-2);
		}

    if (perm == 'repository' || perm == 'webdav')
		{
			if ($F(sele.id) == 'read')
			{
				if (iele.length == 3) iele.remove(0);
				if (permission_admin_user_ids.indexOf(item_id) < 0 && !$('permission_' + item_type + '_' + item_id + '_project_admin').checked && !permission_force_disabled[item_type + '_' + item_id + '_' + perm])
				{
			    iele.disabled = false;
					if (iele.hasClassName('disabled')) iele.removeClassName('disabled');
		    }
			}
			else if ($F(sele.id) == 'none')
			{
				if (iele.length < 3 && !permission_force_read[item_type + '_' + item_id + '_' + perm])
				  iele.insert({ top: new Element('option', { value: "none" }).update("None") });
				if (permission_admin_user_ids.indexOf(item_id) < 0 && !$('permission_' + item_type + '_' + item_id + '_project_admin').checked && !permission_force_disabled[item_type + '_' + item_id + '_' + perm])
				{
			    iele.disabled = false;
					if (iele.hasClassName('disabled')) iele.removeClassName('disabled');
		    }
			}
			else if ($F(sele.id) == 'write' || $F(sele.id) == 'commit')
			{
			  iele.disabled = true;
        if (!iele.hasClassName('disabled')) iele.addClassName('disabled');
			}
	  }
	}
}

function permission_update_trac_perms(prefix, id, action, perms)
{
	for (var i = 0; i < perms.length; i++)
	{
	  var perm_exists = $('permission_' + prefix + '_' + id + '_trac') && $F('permission_' + prefix + '_' + id + '_trac').indexOf(',' + perms[i] + ',') >= 0;
  	if (action == 'add')
		{
			if (!perm_exists) trac_add_perm(prefix, id, perms[i]);
		}
		else
		{
			if (perm_exists) remove_trac_perm(prefix, id, perms[i]);
		}
  }
}

function select_trac_perm(prefix, id, perm)
{
  // close any open select boxes
  if (select_trac_box_perm != null) close_trac_perm();

  var add_button = $('permission_' + prefix + '_' + id + '_new_trac_perm'), select_box = $('trac_perm_select'), container = $('perm_container');
  var add_button_offset = add_button.cumulativeOffset(), container_offset = container.cumulativeOffset();

  // determine where the dialog box should be displayed
  var moveto_top = (add_button_offset.top - container_offset.top), moveto_left = (add_button_offset.left - container_offset.left);
  var edge_distance = (container.getWidth() + 8) - (moveto_left + select_box.getWidth());
  if (edge_distance < 0) moveto_left += edge_distance;

  // place the correct permissions on the dialog box
  var all_perms = prefix == 'user' ? $A(trac_permissions[permission_parent_id]) : $A(trac_permissions[id]);
  var cur_perms = $A($F('permission_' + prefix + '_' + id + '_trac').split(',')).without('');
  var rem_perms = all_perms.reject(function(p) { return cur_perms.include(p); });
  $('trac_perm_select_perms').update('');
  rem_perms.each(function(p) {
    $('trac_perm_select_perms').insert(
		  "<div title='" + p + "' onclick=\"$('permission_modified').value = 'true'; trac_add_perm('" + prefix + "', '" + id + "', '" + p + "')\"" +
			(p == 'TRAC_ADMIN' ? "class='trac_admin_entry'" : '') + ">" + p + "</div>"
		);
  });

  // display the dialog box
  select_box.setStyle({ top: moveto_top + 'px', left: moveto_left + 'px' });
  add_button.hide();
  select_box.show(); select_box.style.display = 'block'; // HACK: don't know why we have to do this manually
  select_trac_box_perm = { prefix: prefix, id: id };
}

function trac_add_perm(prefix, id, perm)
{
  if ($('permission_' + prefix + '_' + id + '_new_trac_perm'))
	{
		var html = "<div id='permission_" + prefix + "_" + id + "_trac_perm_" + perm.toLowerCase() + "' class='trac_perm' " +
	             "style='color: " + (perm == 'TRAC_ADMIN' ? '#440000' : '#444444') + ";'>" + perm +
	             "<div class='trac_perm_delete_shield'></div>" +
	             "<div class='trac_perm_delete' title='Delete Permission' onclick=\"" +
	             "$('permission_modified').value = 'true'; remove_trac_perm('" + prefix + "', '" + id + "', '" + perm.toLowerCase() + "')\">&times;</div></div>";
	  $('permission_' + prefix + '_' + id + '_new_trac_perm').insert({ before: html });
	  $('permission_' + prefix + '_' + id + '_trac').value += perm + ',';
	  if (select_trac_box_perm != null) close_trac_perm();
	}
}

function close_trac_perm()
{
  $('trac_perm_select').hide();
  $('permission_' + select_trac_box_perm.prefix + '_' + select_trac_box_perm.id + '_new_trac_perm').show();
  select_trac_box_perm = null;
}

function remove_trac_perm(prefix, id, perm)
{
  var perm_el = $('permission_' + prefix + '_' + id + '_trac_perm_' + perm.toLowerCase()), perms_field = $('permission_' + prefix + '_' + id + '_trac');
  perm_el.remove();
  perms_field.value = perms_field.value.replace(',' + perm.toUpperCase() + ',', ',');
}

//////////// DASHBOARD ////////////

function get_col_type(item_type)
{
  if (item_type == 'project' || item_type == 'category')
    return 'project';
  else
    return 'user';
}

function get_sec_type(item_type)
{
  if (item_type == 'project' || item_type == 'category')
    return 'category';
  else
    return 'group';
}

function close_all()
{
  if (currently_viewing_project != null)
  {
    hover_out('project', currently_viewing_project, true);
    hide_item('project', currently_viewing_project, true);
  }

  if (currently_viewing_user != null)
  {
    hover_out('user', currently_viewing_user, true);
    hide_item('user', currently_viewing_user, true);
  }
}

function show_item(item_type, index)
{
  close_all();

  $('details_' + item_type + '_' + index).show();
  $('show_details_' + item_type + '_' + index + '_nav').src = '/images/internal/navigate_open.png';
  $('show_details_' + item_type + '_' + index + '_nav').alt = _t('Close');
  if (item_type == 'project') currently_viewing_project = index; else currently_viewing_user = index;
  hover_over(item_type, index);
  $('dash_' + item_type + '_list_' + index).setStyle({ border: '1px solid ' + style_item_select_border });
}

function hide_item(item_type, index, no_change_border)
{
  if (!no_change_border) $('dash_' + item_type + '_list_' + index).setStyle({ border: '1px solid ' + style_item_hover_border });
  $('details_' + item_type + '_' + index).hide();
  $('show_details_' + item_type + '_' + index + '_nav').src = '/images/internal/navigate_close.png';
  $('show_details_' + item_type + '_' + index + '_nav').alt = _t('Open');
  if (item_type == 'project') currently_viewing_project = null; else currently_viewing_user = null;
}

function show_archived_items(item_type, section_id)
{
  var sec_type = get_sec_type(item_type);

  var al = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list');
  var ala = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_action');
  if (al) al.show();
  if (ala) ala.hide();
}

function hide_archived_items(item_type, section_id)
{
  var sec_type = get_sec_type(item_type);

  var al = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list');
	var ala = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_action');
	if (al) al.hide();
	if (ala) ala.show();
}

function hover_over(item_type, index)
{
  if ((item_type == 'project' && index == currently_viewing_project) || (item_type == 'user' && index == currently_viewing_user)) return;
  $('dash_' + item_type + '_list_' + index).setStyle({ background: style_item_hover_background, border: '1px solid ' + style_item_hover_border });
}

function hover_out(item_type, index, override)
{
  if (((item_type == 'project' && index == currently_viewing_project) || (item_type == 'user' && index == currently_viewing_user)) && !override) return;
  $('dash_' + item_type + '_list_' + index).setStyle('background: #fff; border: 1px solid #fff;')
}

// hide archive list if necessary and update archived count
function fix_archived_list(item_type, section_id)
{
  var sec_type = get_sec_type(item_type);
  if ((item_type == 'project' && category_active_map[section_id || 'null'].length == category_map[section_id || 'null'].length) ||
      (item_type == 'user' && group_active_map[section_id || 'null'].length == group_map[section_id || 'null'].length))
  {
    $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_action').hide();
    $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list').hide();
  }
	else if (!$('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list').visible())
	{
    $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_action').show();
	}
}

// update archived count
function fix_archived_count(item_type, section_id)
{
  var sec_type = get_sec_type(item_type);
  var count = item_type == 'project' ? (category_map[section_id || 'null'].length - category_active_map[section_id || 'null'].length) : (group_map[section_id || 'null'].length - group_active_map[section_id || 'null'].length);
  $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_count').update(_t("num_" + (item_type == 'user' ? 'disabled' : 'archived') + "_" + item_type + (count == 1 ? '' : 's'), { count: count }));
}

// searches the items referenced by the given ids for the spot where the given label will fit
// return [ index, id ], where index is the offset of this item (0 = beginning), and id is
// the id of the item right after the insertion point (null = insert at end)
function get_insertion_point(item_type, ids, item_label)
{
  // find element right after where we should move this item
  var insert_index = 0, insert_id = null, count = 0;
  for (var i=0; i < ids.length; i++)
  {
    var item_id = ids[i];
    var label_obj = $('dash_' + item_type + '_list_filter_' + item_id);
		if (!label_obj) continue;
		var label = label_obj.innerHTML;
    insert_index = count;
    insert_id = item_id;
    if (label.toLowerCase() > item_label.toLowerCase()) break;
    if (i == ids.length - 1) { insert_index++; insert_id = null; }
		count++;
  }

  return [ insert_index, insert_id ];
}

function new_item_reset(item_type)
{
  if (item_type == 'project' || item_type == 'group' || item_type == 'category')
    new_item_show(item_type);
  else
  {
    $('user_temp_item_id').value = $('user_display_name').value = $('user_email').value = $('user_username').value = '';
    $('auto_password').checked = true;
    new_user_update_password_enabled();
    new_user_generate_password();
    $('passwords_shown').hide(); $('passwords_hidden').show(); $('passwords_hide_link').hide(); $('passwords_show_link').show();
    $('user_is_administrator').checked = false;

    $('user_display_name').focus();
  }
}

function new_item_show(item_type, creation_type, from_item_id, from_item_title, from_item_vcs, from_item_category)
{
  var col_type = get_col_type(item_type);

  close_all();

  for (var i=0; i<item_types.length; i++)
    if ($('new_' + item_types[i] + '_container').visible())
      new_item_hide(item_types[i]);

  // reset the form; will then need to deal with checkboxes
  $('new_' + item_type).reset();
  if (item_type == 'user')
  {
    if ($('send_welcome').checked) $('custom_welcome_message_tr').show(); else $('custom_welcome_message_tr').hide();
    if ($('use_custom_welcome_message').checked) $('welcome_message_tr').show(); else $('welcome_message_tr').hide();
    $('welcome_message').value = $('welcome_message_original').value;
    new_user_update_password_enabled();
    if ($('auto_password').checked) new_user_generate_password();
    $('passwords_shown').hide(); $('passwords_hidden').show(); $('passwords_hide_link').hide(); $('passwords_show_link').show();
  }

  // handle forks and copies
  if (creation_type == 'fork' || creation_type == 'copy')
  {
    $('project_new_title').update(_t('new_project_' + creation_type) + ' ' + from_item_title);
    $('project_creation_type').value = creation_type;
    $('project_from_project_id').value = from_item_id;
    $('project_new_system_input').hide();
    $('project_new_system_no_input').show();
    $('project_new_system_no_input').update(vcs_types[from_item_vcs]);
    $('project_category_id').value = from_item_category;
    $('project_new_create_and_add_button').hide();
  }
  else
  {
    $('project_new_title').update(_t("New Project"));
    $('project_creation_type').value = '';
    $('project_from_project_id').value = '';
    $('project_new_system_input').show();
    $('project_new_system_no_input').hide();
    $('project_new_create_and_add_button').show();
  }

  $('new_' + item_type + '_container').show();
  $(col_type + '_filter_container').hide();
  $('new_' + col_type + '_actions').hide();
  $(item_type + '_' + (item_type == 'project' ? 'title' : (item_type == 'user' ? 'display_name' : (item_type == 'category' ? 'title' : 'title')))).focus();
}

function new_item_hide(item_type)
{
  var col_type = get_col_type(item_type);
  var sec_type = get_sec_type(item_type);

  $('new_' + item_type + '_container').hide();
  if (item_ids[col_type].length + item_ids[sec_type].length > 0) $(col_type + '_filter_container').show();
  $('new_' + col_type + '_actions').show();
}

function generate_id()
{
  return Math.ceil(Math.random() * 100000) + 100000;
}

function new_user_generate_password()
{
  var pw_plain = Math.random().toString(36).substr(2, 8);
  var pw_x = "XXXXXXXX";
  $('user_password').value = $('password_confirmation').value = pw_x;
  $('password_plain').value = $('password_confirmation_plain').value = pw_plain;
}

function new_user_clear_password()
{
  $('user_password').value = $('password_confirmation').value = $('password_plain').value = $('password_confirmation_plain').value = '';
  new_user_hide_password();
}

function new_user_show_password()
{
  $('passwords_hidden').hide();
  $('passwords_shown').show();
  $('passwords_show_link').hide();
  $('passwords_hide_link').show();
}

function new_user_hide_password()
{
  $('passwords_shown').hide();
  $('passwords_hidden').show();
  $('passwords_hide_link').hide();
  $('passwords_show_link').show();
}

function new_user_update_password_enabled()
{
  $('user_password').disabled = $('password_confirmation').disabled = $('password_plain').disabled = $('password_confirmation_plain').disabled = !!$('auto_password').checked;
  if ($('auto_password').checked) $('passwords_show_hide_div').show(); else $('passwords_show_hide_div').hide();
}

function add_item(id, section_id, item_type, item_label, item_description, item_sub_1, item_sub_2, item_sub_3)
{
  var col_type = get_col_type(item_type);
  var sec_type = get_sec_type(item_type);
  var is_section = item_type == 'category' || item_type == 'group';
  if (section_id != null) section_id = section_id.strip();
  if (section_id != null && section_id == '') section_id = null;

  // define the html of the item we wish to add
  var content = "";
  if (item_type == 'project' || item_type == 'user')
  {
    content = "<li id='dash_" + item_type + "_list_" + id + "' onmouseover=\"hover_over('" + item_type + "', " + id + ")\" " +
    "onmouseout=\"hover_out('" + item_type + "', " + id + ")\" style='position: relative; " + (section_id ? 'padding-left: 15px' : '') + "'>" +
    "<div style='position: relative;'><table style='margin: 0; padding: 0; border: 0; width: 100%' cellpadding='0' cellspacing='0'>" +
    "<tr valign='top'><td><strong id='dash_" + item_type + "_list_filter_" + id + "'>" + item_label + "</strong></td><td></td></tr>" +
    "</table><div class='settings'>" +
    "<span id='dash_" + item_type + "_list_filter2_" + id + "'>" + item_sub_1 + "</span>" +
    (item_sub_2 ? (" / " + item_sub_2 + (item_sub_3 ? (" / <span style='color: #440000'>" + item_sub_3 + "</span>") : '')) : '')
     + "</div>" +
    (item_description == null || item_description == '' ? '' : ("<p>" + item_description + "</p>")) +
    "<div id='" + item_type + "_" + id + "_spinner' style='position: absolute; top: 5px; right: 5px;'>" + html_spinner_image + "</div>" +
    "<div id='" + item_type + "_" + id + "_error' style='display: none; position: absolute; font-size: 11px; left: 30px; top: 15px; right: 30px; vertical-align: middle; background-color: pink; border: 1px solid red; padding: 5px; color: black;'>" +
    "<a href='#' onclick=\"$('dash_" + item_type + "_list_" + id + "').hide();\" style='position: absolute; font-size: 10px; top: 2px; right: 4px;'>Close</a>" +
    "<div id='" + item_type + "_" + id + "_error_inner' style='padding-right: 25px;'></div>" +
    "</div>" +
    "</li>";
  }
  else
  {
    content = "<h2 id='dash_" + item_type + "_list_" + id + "' class='section' style='font-size: 18px;'>" +
              "<span id='dash_" + item_type + "_list_filter_" + id +"'>" + item_label + "</span> " +
							"<span style='font-size: 11px'>- <a href='/" + (item_type == 'category' ? 'categories' : 'groups') + "/" + id + "/edit'>" + _t("Settings") + "</a></span>" +
							"</h2>" +
              "<div id='dash_" + item_type + "_list_" + id + "_empty_message' style='display: block; padding: 5px; color: gray;'>" + _t('empty_message_' + item_type) + "</div>" +
              "<ul id='dash_" + item_type + "_" + id + "_" + col_type + "_list'></ul>";
  }

  // find element right after where we should insert this item
  var ids = is_section ? item_ids[item_type] : (item_type == 'project' ? (category_map[section_id || 'null'] || []) : (group_map[section_id || 'null'] || []));
  var ip = get_insertion_point(item_type, ids, item_label); var insert_index = ip[0], insert_id = ip[1];

  // insert the item
  if (insert_id == null)
  {
    if (is_section)
      Element.insert('dash_' + item_type + '_list', { bottom: content });
    else
      Element.insert('dash_' + sec_type + '_' + (section_id || '_none_') + '_' + item_type + '_list', { bottom: content });
  }
  else
    Element.insert('dash_' + item_type + '_list_' + insert_id, { before: content });

  if ((item_type == 'project' || item_type == 'user') && section_id)
    $('dash_' + (item_type == 'project' ? 'category' : 'group') + '_list_' + section_id + '_empty_message').hide();

  // update variables
  if (is_section)
  {
    item_ids[item_type].splice(insert_index, 0, id);
    if (item_type == 'category') category_map[id || 'null'] = []; else group_map[id || 'null'] = [];
  }
  else
  {
    item_ids[item_type].push(id);
    if (item_type == 'project')
    {
      if (!category_map[section_id || 'null']) category_map[section_id || 'null'] = [];
      category_map[section_id || 'null'].splice(insert_index, 0, id);
    }
    else
    {
      if (!group_map[section_id || 'null']) group_map[section_id || 'null'] = [];
      group_map[section_id || 'null'].splice(insert_index, 0, id);
    }
  }
}

function create_item(id, item_type, abbreviation, old_id, section_id)
{
  // at least project exists now
  $("project_empty_message").hide();
  $("project_filter_container").show();

  // update variables
  item_ids[item_type][item_ids[item_type].indexOf(old_id)] = id;
  if (item_type == 'project')
  {
    active_projects.push(id);
    project_abbreviations.push(abbreviation);
    category_map[section_id || 'null'][category_map[section_id || 'null'].indexOf(old_id)] = id;
    category_active_map[section_id || 'null'] = category_active_map[section_id || 'null'] || [];
    category_active_map[section_id || 'null'].push(id);
  }
  else
  {
    active_users.push(id);
    user_usernames.push(abbreviation);
    group_map[section_id || 'null'][group_map[section_id || 'null'].indexOf(old_id)] = id;
    group_active_map[section_id || 'null'] = group_active_map[section_id || 'null'] || [];
    group_active_map[section_id || 'null'].push(id);
  }
}

function create_section(item_type, section_id, section_title)
{
  var col_type = get_col_type(item_type);

  add_item(section_id, null, item_type, section_title);

  if (item_type == 'category')
	{
	  category_titles.push(section_title);
	  category_active_map[section_id] = [];
	}
	else
	{
	  group_titles.push(section_title);
	  group_active_map[section_id] = [];
	}

  $('page_flash_notice').innerHTML = '<div>' + _t(item_type + '_capitalized') + ' "' + section_title + '" ' + _t("created") + '.</div>'
  Effect.SlideDown('page_flash_notice');
  if (item_type == 'category')
	{
	  $("project_empty_message").hide();
    $("project_filter_container").show();
	}

	Element.insert(col_type + '_' + item_type + '_id', { bottom: "<option value='" + section_id + "'>" + section_title + "</option>" });

  for (var i=0; i < item_ids[col_type].length; i++)
    Element.insert(col_type + '_' + item_ids[col_type][i] + '_field_' + item_type + '_id', { bottom: "<option value='" + section_id + "'>" + section_title + "</option>" });
}

function move_item(id, item_type, src_section, dest_section)
{
  var sec_type = get_sec_type(item_type);
  var src_item = $('dash_' + item_type + '_list_' + id);
  var item_label = $('dash_' + item_type + '_list_filter_' + id).innerHTML;
  if (item_type == 'project')
  {
    if (!category_map[dest_section || 'null']) category_map[dest_section || 'null'] = [];
  }
  else
  {
    if (!group_map[dest_section || 'null']) group_map[dest_section || 'null'] = [];
  }
  var src_ids = (item_type == 'project' ? category_map[src_section || 'null'] : group_map[src_section || 'null']);
  var dest_ids = (item_type == 'project' ? category_map[dest_section || 'null'] : group_map[dest_section || 'null']);
  var item_map = (item_type == 'project' ? project_map : user_map);
  var current_index = src_ids.indexOf(id);

  // find element right after where we should move this item
  var ip = get_insertion_point(item_type, dest_ids, item_label); var insert_index = ip[0], insert_id = ip[1];

  // move the item
  var section = $('dash_' + sec_type + '_' + (dest_section || '_none_') + '_' + item_type + '_list');
  if (insert_id == null)
    section.appendChild(src_item);
  else
  {
    var next_item = $('dash_' + item_type + '_list_' + insert_id);
    next_item.parentNode.insertBefore(src_item, next_item);
  }
  src_item.style.paddingLeft = dest_section == null ? '3px' : '15px';

  // update variables
  src_ids.splice(current_index, 1);
  dest_ids.splice(insert_index, 0, id);
  for (var i=0; i < item_ids[item_type].length; i++)
  {
    var item_id = item_ids[item_type][i];
    if (item_map[item_id || 'null'] == src_section) item_map[item_id || 'null'] = dest_section;
  }

  // update the sections
  var src_section_empty = src_section ? $('dash_' + sec_type + '_list_' + src_section + '_empty_message') : null;
  var dest_section_empty = dest_section ? $('dash_' + sec_type + '_list_' + dest_section + '_empty_message') : null;
  if (src_section_empty) { if (src_ids.length == 0) src_section_empty.show(); else src_section_empty.hide(); }
  if (dest_section_empty) { if (dest_ids.length == 0) dest_section_empty.show(); else dest_section_empty.hide(); }
}

function activate_item(id, item_type, section_id, abbreviation)
{
  var sec_type = get_sec_type(item_type);
  var item = $('dash_' + item_type + '_list_' + id);
	var item_label = $('dash_' + item_type + '_list_filter_' + id).innerHTML;
  var activated_list = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_' + item_type + '_list');
  var active_ids = (item_type == 'project' ? category_active_map[section_id || 'null'] : group_active_map[section_id || 'null']);
  var ids = (item_type == 'project' ? active_projects : active_users);

  // find element right after where we should move this item
	var ip = get_insertion_point(item_type, active_ids, item_label); var insert_index = ip[0], insert_id = ip[1];
	var ip2 = get_insertion_point(item_type, ids, item_label); var active_items_insert_index = ip[0];

  // move the item
  if (insert_id == null)
    activated_list.appendChild(item);
  else
  {
    var next_item = $('dash_' + item_type + '_list_' + insert_id);
    next_item.parentNode.insertBefore(item, next_item);
  }

  // transform the item
	item.setStyle({ marginBottom: '10px', paddingLeft: (parseInt(item.style.paddingLeft) == 15 ? 3 : 15) + 'px' });
  $('dash_' + item_type + '_list_' + id + '_title').setStyle({ display: 'table' });
  $('dash_' + item_type + '_list_' + id + '_content_archived').hide();
  $('dash_' + item_type + '_list_' + id + '_content').show();
  $(item_type + '_' + id + '_spinner').hide();
  $(item_type + '_' + id + '_spinner').setStyle({ marginTop: '5px', marginRight: '5px' });
  $('dash_' + item_type + '_list_' + id + '_content_archived_actions').show();

  // update variables
  if (item_type == 'project')
  {
    active_projects.splice(active_items_insert_index, 0, id);
    category_active_map[section_id || 'null'].splice(insert_index, 0, id);
  }
  else
  {
    active_users.splice(active_items_insert_index, 0, id);
    group_active_map[section_id || 'null'].splice(insert_index, 0, id);
  }

  // handle archived items
	fix_archived_list(item_type, section_id);
  fix_archived_count(item_type, section_id);
}

function deactivate_item(id, item_type, section_id, abbreviation)
{
  var sec_type = get_sec_type(item_type);
  var item = $('dash_' + item_type + '_list_' + id);
  var item_label = $('dash_' + item_type + '_list_filter_' + id).innerHTML;
  var deactivated_list = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_ul');
  var deactivated_list_count = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_count');
  var ids = (item_type == 'project' ? category_map[section_id || 'null'] : group_map[section_id || 'null']);
  var active_ids = (item_type == 'project' ? category_active_map[section_id || 'null'] : group_active_map[section_id || 'null']);
  var inactive_ids = ids.reject(function(s) { return active_ids.indexOf(s) >= 0; });

  // find element right after where we should move this item
  var insert_id = null;
  for (var i=0; i < inactive_ids.length; i++)
  {
    var item_id = inactive_ids[i];
    var label = $('dash_' + item_type + '_list_filter_' + item_id).innerHTML;
    insert_id = item_id;
    if (label.toLowerCase() > item_label.toLowerCase()) break;
    if (i == inactive_ids.length - 1) insert_id = null;
  }

  // move the item
  if (insert_id == null)
    deactivated_list.appendChild(item);
  else
  {
    var next_item = $('dash_' + item_type + '_list_' + insert_id);
    next_item.parentNode.insertBefore(item, next_item);
  }

  // transform the item
  item.setStyle({ marginBottom: '2px', paddingLeft: (parseInt(item.style.paddingLeft) == 15 ? 30 : 15) + 'px' });
  $('dash_' + item_type + '_list_' + id + '_title').setStyle({ display: 'none' });
  $('dash_' + item_type + '_list_' + id + '_content_archived').show();
  $('dash_' + item_type + '_list_' + id + '_content').hide();
  $(item_type + '_' + id + '_spinner').hide();
  $(item_type + '_' + id + '_spinner').setStyle({ marginTop: '5px', marginRight: '5px' });
  $('show_details_' + item_type + '_' + id).show();

  // update variables
  if (item_type == 'project')
  {
    active_projects.splice(active_projects.indexOf(id), 1);
    var cam_loc = category_active_map[section_id || 'null'].indexOf(id);
    if (cam_loc >= 0) category_active_map[section_id || 'null'].splice(cam_loc, 1);
  }
  else
  {
    active_users.splice(active_users.indexOf(id), 1);
    var cam_loc = group_active_map[section_id || 'null'].indexOf(id);
    if (cam_loc >= 0) group_active_map[section_id || 'null'].splice(cam_loc, 1);
  }

  // handle archived items
  fix_archived_list(item_type, section_id);
  fix_archived_count(item_type, section_id);
}

function delete_item(id, item_type, section_id, abbreviation)
{
  var sec_type = get_sec_type(item_type);

  // delete the item
  Effect.Fade("dash_" + item_type + "_list_" + id);

  // update variables
  var sectionids = (item_type == 'project' ? category_map[section_id || 'null'] : group_map[section_id || 'null']), itemids = item_ids[item_type];
  sectionids.splice(sectionids.indexOf(id), 1);
  itemids.splice(itemids.indexOf(id), 1);
  if (item_type == 'project')
  {
    active_projects.splice(active_projects.indexOf(id), 1);
    var cam_loc = category_active_map[section_id || 'null'].indexOf(id);
		if (cam_loc >= 0) category_active_map[section_id || 'null'].splice(cam_loc, 1);
  }
  else
  {
    active_users.splice(active_users.indexOf(id), 1);
    var cam_loc = group_active_map[section_id || 'null'].indexOf(id);
		if (cam_loc >= 0) group_active_map[section_id || 'null'].splice(cam_loc, 1);
  }
  delete (item_type == 'project' ? project_map[id || 'null'] : user_map[id || 'null']);
  project_abbreviations.splice(project_abbreviations.indexOf(abbreviation));

  // update the sections
  var section_empty = section_id ? $('dash_' + sec_type + '_list_' + section_id + '_empty_message') : null;
  if (section_empty) { if (sectionids.length == 0) section_empty.show(); else section_empty.hide(); }

  // handle archived items
  fix_archived_list(item_type, section_id);
  fix_archived_count(item_type, section_id);
}

// this function filters the list of elements by hiding ones that don't match and showing
// ones that do.
function filter_list(item_type, filter_string)
{
  var sec_type = get_sec_type(item_type);
  var section_ids = item_ids[sec_type]; section_ids.push(null);
  var ids = item_type == 'project' ? active_projects : active_users;
  filter_string = filter_string.toLowerCase().strip();
  var visible_sections = [];

	for (var i=0; i < ids.length; i++)
  {
    var id = ids[i];
    var f = $('dash_' + item_type + '_list_filter_' + id);
		if (!f) continue; // only deal with visible items
		var label1 = f.innerHTML.toLowerCase() || '';
    var label2 = $('dash_' + item_type + '_list_filter2_' + id).innerHTML.toLowerCase() || '';
    var element = $('dash_' + item_type + '_list_' + id);

    if (label1.indexOf(filter_string) >= 0 || label2.indexOf(filter_string) >= 0)
    {
      element.show();
      var section_id = item_type == 'project' ? project_map[id || 'null'] : user_map[id || 'null'];
      if (section_id && visible_sections.indexOf(section_id) < 0) visible_sections.push(section_id);
    }
    else
      element.hide();
  }

  // only show sections with contents; if the filter field is blank, then show all sections
  for (var i=0; i < section_ids.length; i++)
  {
    var section_id = section_ids[i];
		var section = section_id ? $('dash_' + sec_type + '_list_' + section_id) : null;
    var section_empty = section_id ? $('dash_' + sec_type + '_list_' + section_id + '_empty_message') : null;
    var section_deactivated_action = $('dash_' + sec_type + '_' + (section_id || '_none_') + '_archived_list_action');
		var num_inactive = item_type == 'project' ? ((category_map[section_id || 'null'] ? category_map[section_id || 'null'].length : 0) - (category_active_map[section_id || 'null'] ? category_active_map[section_id || 'null'].length : 0)) : ((group_map[section_id || 'null'] ? group_map[section_id || 'null'].length : 0) - (group_active_map[section_id || 'null'] ? group_active_map[section_id || 'null'].length : 0));

		// hide inactive items if any kind of filtering is going on
		hide_archived_items(sec_type, section_id);
    if (filter_string == '' && num_inactive > 0)
		{
		  if (section_deactivated_action) section_deactivated_action.show();
		}
		else
		{
			if (section_deactivated_action) section_deactivated_action.hide();
		}

    if (section)
		{
			if (filter_string == '' || visible_sections.indexOf(section_id) >= 0)
			{
				section.show();
				var section_contents = (item_type == 'project' ? category_map[section_id || 'null'] : group_map[section_id || 'null']);
				if (filter_string == '' && (section_contents == null || section_contents.length == 0))
				{
					if (section_empty) section_empty.show();
				}
				else
				{
					if (section_empty) section_empty.hide();
				}
			}
			else
			{
				if (section) section.hide();
				if (section_empty) section_empty.hide();
			}
	  }
  }
}

function check_inputs(item_type)
{
  var errors = [];
  if (item_type == 'project')
  {
    var title = $F('project_title'), abbr = $F('project_abbreviation').toLowerCase();

    if (title == null || title.blank())
      errors.push(_t("Title cannot be blank."));
    if (abbr == null || abbr.blank())
      errors.push(_t("Abbreviation cannot be blank."));
    else if (!abbr.match(regexs['project_abbreviation']))
      errors.push(_t("Abbreviation must only contain the letters a-z, numbers, and/or dashes."));
    else if (project_abbreviations.indexOf(abbr) >= 0)
      errors.push(_t("Abbreviation has already been taken."));
  }
  else if (item_type == 'user')
  {
    var display_name = $F('user_display_name'), username = $F('user_username').toLowerCase(), email = $F('user_email');
    var password = $F('user_password'), password_confirm = $F('password_confirmation');

    if (display_name == null || display_name.blank())
      errors.push(_t("Display name cannot be blank."));
    if (email == null || email.blank())
      errors.push(_t("Email cannot be blank."));
    else if (!email.match(regexs['user_email']))
      errors.push(_t("Email address is in an invalid format."));
    if (username == null || username.blank())
      errors.push(_t("Username cannot be blank."));
    else if (!username.match(regexs['user_username']))
      errors.push(_t("Username must only contain the letters a-z, numbers, and/or the symbols:") + " . _ @");
    else if (user_usernames.indexOf(username) >= 0)
      errors.push(_t("Username has already been taken."));
    if (password == null || password_confirm == null || password.blank() || password_confirm.blank() || password.strip() != password_confirm.strip())
     errors.push(_t("Password and confirmation must match and not be blank."));
  }
  else if (item_type == 'category')
  {
    var title = $F('category_title');

    if (title == null || title.blank())
      errors.push(_t("Name cannot be blank."));
    else if (category_titles.indexOf(title) >= 0)
      errors.push(_t("Category name has already been taken."));
  }
  else if (item_type == 'group')
  {
    var title = $F('group_title');

    if (title == null || title.blank())
      errors.push(_t("Name cannot be blank."));
    else if (group_titles.indexOf(title) >= 0)
      errors.push(_t("Group name has already been taken."));
  }

  if (errors.length == 0)
    return true;
  else
  {
    var msg = ''; for (var i=0; i<errors.length; i++) msg += ' * ' + errors[i] + "\n";
    alert(_t("Invalid input. Please correct the following errors and try creating the %{item_type} again:", { item_type: item_type }) + "\n\n" + msg);
    return false;
  }
}

function before_item_create(item_type, section_id, sub_2)
{
  var id = generate_id(), is_user = item_type == 'user';
  $(item_type + '_temp_item_id').value = id;

  // hash the password so that we can send it over a (potentially) non-ssl connection
	if (item_type == 'user') {
		if ($('auto_password').checked) $('user_password').value = $('password_confirmation').value = $('password_plain').value;
		$('password_plain').value = $('password_confirmation_plain').value = '';
		$('user_password').disabled = $('password_confirmation').disabled = false;
	}

  add_item(
    id, section_id, item_type, is_user ? $F('user_display_name') : $F('project_title'), is_user ? null : $F('settings_description'),
    is_user ? $F('user_username') : $F('project_abbreviation'), sub_2, is_user ? ($('user_is_administrator').checked ? '[admin]' : null) : null
  )
}

function after_item_create(item_type)
{
  if (item_type == 'category' || item_type == 'group')
  {
    new_item_hide(item_type);
    return;
  }

  $('page_flash_notice').innerHTML = item_type == 'user' ?
    ('<div>' + _t('User "%{name}" being created.', { name: $F('user_display_name') }) + '</div>') :
    ('<div>' + _t('Project "%{name}" being created.', { name: $F('project_title') }) + '</div>');
  Effect.SlideDown('page_flash_notice');
  if ((item_type == 'user' && user_add_another) || (item_type == 'project' && project_add_another))
    new_item_reset(item_type);
  else
    new_item_hide(item_type);
}

function after_item_delete(id, item_type, item_title)
{
  close_all();

  if ($('dash_' + item_type + '_list_' + id + '_content').visible())
    $('show_details_' + item_type + '_' + id).hide();
	else
   $('dash_' + item_type + '_list_' + id + '_content_archived_actions').hide();

  $(item_type + '_' + id + '_spinner').show();

  $('page_flash_notice').innerHTML = item_type == 'user' ?
    ('<div>' + _t('User "%{name}" being deleted.', { name: item_title }) + '</div>') :
    ('<div>' + _t('Project "%{name}" being deleted.', { name: item_title }) + '</div>');
  Effect.SlideDown('page_flash_notice');
}

function after_item_archive(id, item_type, item_title)
{
  close_all();

  $('show_details_' + item_type + '_' + id).hide();
	$(item_type + '_' + id + '_spinner').show();

  $('page_flash_notice').innerHTML = item_type == 'user' ?
    ('<div>' + _t('User "%{name}" being disabled.', { name: item_title }) + '</div>') :
    ('<div>' + _t('Project "%{name}" being archived.', { name: item_title }) + '</div>');
  Effect.SlideDown('page_flash_notice');
}

function after_item_restore(id, item_type, item_title)
{
  close_all();

  $('dash_' + item_type + '_list_' + id + '_content_archived_actions').hide();
	$(item_type + '_' + id + '_spinner').show();

  $('page_flash_notice').innerHTML = item_type == 'user' ?
    ('<div>' + _t('User "%{name}" being enabled.', { name: item_title }) + '</div>') :
    ('<div>' + _t('Project "%{name}" being restored.', { name: item_title }) + '</div>');
  Effect.SlideDown('page_flash_notice');
}

function section_toggle(section_type, section_id, active_items_empty, inactive_items_empty)
{
  var item_type = get_col_type(section_type);
  var id = section_id || '_none_';
  var list_title = $('dash_' + section_type + '_list_' + id);
  var empty_list = $('dash_' + section_type + '_list_' + id + '_empty_message');
  var active_list = $('dash_' + section_type + '_' + id + '_' + item_type + '_list');
  var inactive_list = $('dash_' + section_type + '_' + id + '_archived_list');
  var inactive_list_toggle = $('dash_' + section_type + '_' + id + '_archived_list_action');
  var toggle_icon = $('dash_' + section_type + '_list_' + id + '_toggle');
  var is_expanded = toggle_icon.src.indexOf('expanded') > 0;

  if (is_expanded)
  {
    empty_list.hide();
    active_list.hide();
    inactive_list.hide();
    inactive_list_toggle.hide();
    toggle_icon.src = '/images/folder_tree_branch_collapsed_icon.gif';
    list_title.setStyle({ borderBottomWidth: '0px', marginBottom: '10px' });
  }
  else
  {
    if (active_items_empty) empty_list.show();
    active_list.show();
    if (!inactive_items_empty) inactive_list_toggle.show();
    toggle_icon.src = '/images/folder_tree_branch_expanded_icon.gif';
    list_title.setStyle({ borderBottomWidth: '1px', marginBottom: '0px' });
  }
}
