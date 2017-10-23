<nav class="navbar navbar-inverse">
  <div class="container-fluid">
    <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
      <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href="{{ URL::route('index') }}">CIR</a>
    </div>

    <!-- Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
      <form class="navbar-form navbar-left" role="search" id="search-games-global" 
      onkeyup="$.searchGlobal({{ $allgames->count() }})">
      <div class="form-group">
        <input id="games-global-search" type="text" name="games-global-search" class="form-control" placeholder="Search games...">
      </div>
      <div id="search-result-layer">
        <span id="global-search-result" style="display: none;">
          <!-- Break -->
          <ul class="nav nav-pills nav-stacked span2" id="global-games-search-ul">
            
          </ul>
          <!-- Break -->
        </span>
      </div>
    </form>
      <ul class="nav navbar-nav navbar-right">
        @if (Auth::check())
          <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
              {{ Auth::user()->username }}<span class="caret"></span></a>
            <ul class="dropdown-menu">
              <li><a href="{{ URL::route('profile', Auth::user()->id) }}">Profile</a></li>
              <li><a href="{{ URL::route('settings') }}">Settings</a></li>
              <li role="separator" class="divider"></li>
              <li><a href="{{ URL::route('logout') }}">Logout</a></li>
            </ul>
          </li>
        @elseif (\Request::route()->getName() != 'register-new') 
          <a href="{{ URL::route('register-new') }}" id="register">No Account? Register here</a>
          {{ Form::open(array('url' => route('login'), 'method' => 'post', 'class' => 'form-inline', 'value' => '{!! csrf_field() !!}')) }}
          <div class="inline-form-wrapper">
            <div class="form-group">
              {{ Form::text('username', NULL, array('class' => 'text form-control', 'required' => 'required', 'placeholder' => 'Username')) }}
            </div>
            <div class="form-group">
              {{ Form::password('password', array('class' => 'text form-control', 'required' => 'required', 'placeholder' => 'Password')) }}
            </div>
              {{ Form::submit('Login', array('class' => 'submit btn btn-default')) }}
          </div>
              <!-- Add recover password -->
          {{ Form::close() }}
        @endif
      </ul>
    </div><!-- /.navbar-collapse -->
  </div><!-- /.container-fluid -->
</nav>