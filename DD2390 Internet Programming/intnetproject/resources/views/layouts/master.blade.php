<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8" />
        <meta name="description" content="{{ $description or '' }}" />
        <meta name="_token" content="{{ csrf_token() }}"/>
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="shortcut icon" href="{{ asset('favicon.ico') }}" />
        <link rel="icon" href="{{ asset('favicon.ico') }}" type="image/x-icon"/>
        <title>@yield('title')</title>
        {{ Html::style('css/app.css') }}
        {{ Html::style('css/style.css') }}
        {{ Html::script('js/jquery-1.12.0.js') }}
        {{ Html::script('js/bootstrap.min.js') }}
        {{ Html::script('js/globalsearch.js') }}
        @yield('scripts')
        <!--{{ Html::script('js/getposts.js') }}-->
        <script>
        $(function() {
            $('div.element').click(function() {
                $('div.element').removeClass('active');
                $(this).addClass('active');
            });
        });
        </script>
        <script type="text/javascript">
            var APP_URL = {!! json_encode(url('/')) !!};
        </script>
    </head>
    <body>
        <div id="page-wrap">
            @include('includes.site-elements.menu')

            @section('left-sidebar')
                <div id="sidebar" class="cf">
                    @include('includes.site-elements.left-panel')
                    @include('includes.site-elements.latest-posts')
                    <div class="clear"></div>
                </div>
            @show

            <div class="container center main-content">
                @yield('content')
            </div>
            <div class="clear"></div>
            <div class="push"></div>
        </div>
        @include('includes.site-elements.footer')
    </body>
</html>
