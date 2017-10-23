<?php

// Index
Breadcrumbs::register('index', function($breadcrumbs)
{
    $breadcrumbs->push('Home', route('index'));
});

// Index > About
Breadcrumbs::register('about', function($breadcrumbs)
{
    $breadcrumbs->parent('index');
    $breadcrumbs->push('About', route('about'));
});

// Index > Contact
Breadcrumbs::register('contact', function($breadcrumbs)
{
    $breadcrumbs->parent('index');
    $breadcrumbs->push('Contact', route('contact'));
});

// Index > [Category]
Breadcrumbs::register('games', function($breadcrumbs, $category)
{
    $breadcrumbs->parent('index');
    $breadcrumbs->push($category->name, route('games', $category->token));
});

// Index > [Category] > [Game]
Breadcrumbs::register('game', function($breadcrumbs, $category, $game)
{
    $breadcrumbs->parent('games', $category);
    $breadcrumbs->push($game->title, route('game', array($category->token, $game->token)));
    //$breadcrumbs->push($category->name, route('games', $category->token));
});

/**
 * 
 * THESE ARE EXAMPLES FROM A TEMPLATE TO UNDERSTAND HOW IT WORKS
 * 
 */

// Home > Blog
Breadcrumbs::register('blog', function($breadcrumbs)
{
    $breadcrumbs->parent('home');
    $breadcrumbs->push('Blog', route('blog'));
});

// Home > Blog > [Category]
Breadcrumbs::register('category', function($breadcrumbs, $category)
{
    $breadcrumbs->parent('blog');
    $breadcrumbs->push($category->title, route('category', $category->id));
});

// Home > Blog > [Category] > [Page]
Breadcrumbs::register('page', function($breadcrumbs, $page)
{
    $breadcrumbs->parent('category', $page->category);
    $breadcrumbs->push($page->title, route('page', $page->id));
});