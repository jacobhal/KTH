@if($s = Session::get('success'))
	<?php $success = $s; ?>
@endif 

@if(isset($success))
	@if (is_array($success) && count($success) > 1)
		<ul class="alert alert-success">
			@foreach ($success as $s)
				<li>{{ $s }}</li>
			@endforeach
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</ul>
	@elseif(is_array($success) && count($success) > 0)
		<p class="alert alert-success">
			{{ $success[0] }}
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</p>
	@else
		<p class="alert alert-success">
			{{ $success }}
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</p>
	@endif
@endif