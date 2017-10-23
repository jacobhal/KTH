@if($e = Session::get('error'))
	<?php $error = $e; ?>
@endif 

@if(isset($error))
	@if (is_array($error) && count($error) > 1)
		<ul class="alert alert-danger">
			@foreach ($error as $s)
				<li>{{ $s }}</li>
			@endforeach
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</ul>
	@elseif(is_array($error) && count($error) == 1)
		<p class="alert alert-danger">
			{{ $error[0] }}
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</p>
	@else
		<p class="alert alert-danger">
			{{ $error }}
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</p>
	@endif
@endif