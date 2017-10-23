<!-- Stored in resources/views/child.blade.php -->

@extends('layouts.master')

@section('title', 'CIR')

@section('content')
    @include('includes.messages.index')
    <h1>Welcome to Can I Run It</h1>
    <hr>
    <p style="margin-bottom: 10px;">
      This is a website where people can comment on games and describe how well they run it.
      In their profiles, you can check what their specifications are so that you can compare them to your own
      which might give you an idea of how well the game will run for you.
    </p>
     <!-- Carousel-->
    <div id="myCarousel" class="carousel slide" data-interval="4000">
        <!-- Carousel indicators -->
        <ol class="carousel-indicators">
            <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
            <li data-target="#myCarousel" data-slide-to="1"></li>
            <li data-target="#myCarousel" data-slide-to="2"></li>
        </ol>   
      <div class="carousel-inner">
        <div class="item active">
          <img src="images/msi-970.jpg">
            <div class="carousel-caption">
              <h1>MSI GTX 970 Gaming</h1>
              <p class="lead">The new graphics card from MSI is awesome!</p>
          </div>
        </div>
        <div class="item">
          <img src="images/cooler-master-hafx.jpg" alt="">
            <div class="carousel-caption">
              <h1>Cooler Master HAF-X</h1>
              <p class="lead">The HAF-X computer case from Cooler Master has incredible cooling, massive space for all of the latest components and a design that makes replacing components easy.</p>
          </div>
        </div>
        <div class="item">
          <img src="images/samsung-evo.jpeg" alt="">
            <div class="carousel-caption">
              <h1>Samsung EVO SSD</h1>
              <p class="lead">The Samsung EVO SSD is one of the most popular SSD:s around, and rightly so.</p>
          </div>
        </div>
      </div>
      <!-- Carousel controls -->
    <a class="carousel-control left" href="#myCarousel" data-slide="prev">
        <span class="glyphicon glyphicon-chevron-left"></span>
    </a>
    <a class="carousel-control right" href="#myCarousel" data-slide="next">
        <span class="glyphicon glyphicon-chevron-right"></span>
    </a>
    </div><!-- /.carousel -->
    <div class="main-text">

    </div>


@endsection
