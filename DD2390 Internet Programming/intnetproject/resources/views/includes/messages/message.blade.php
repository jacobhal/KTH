@if($w = Session::get('warning'))
	<?php $warning = $w; ?>
@endif 

@if($m = Session::get('message'))
	<?php $message = $m; ?>
@endif 

@if(isset($warning))
	<?php $message = $warning; ?>
@endif

@if(isset($message))
	@if (is_array($message) && count($message) > 1)
		<ul class="alert alert-warning">
			@foreach ($message as $s)
				<li>{{ $s }}</li>
			@endforeach
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</ul>
	@elseif(is_array($message) && count($message) == 1)
		<p class="alert alert-warning">
			{{ $message[0] }}
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</p>
	@else
		<p class="alert alert-warning" style="margin-top: 10px">
			{{ $message }}
			<a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
		</p>
	@endif
@endif