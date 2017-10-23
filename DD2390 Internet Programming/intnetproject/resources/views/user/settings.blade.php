@extends('layouts.master')

@section('title')
Profile settings
@endsection

@section('content')
    <div id="settings-wrapper">
        <h2>Settings</h2>
        <hr>
        @include('includes.messages.index')

        @if(Auth::check())
        {{ Form::open(array('route' => array('settings-update'), 'method' => 'post', 'class' => 'settings-update-form', 'value' => '{!! csrf_field() !!}')) }}
                
                <div class="form-group">
                  {{ Form::label('cpu', 'CPU') }}
                  {{ Form::text('cpu', $settings->cpu, array('class' => 'text form-control', 'placeholder' => 'CPU', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('gpu', 'GPU') }}
                  {{ Form::text('gpu', $settings->gpu, array('class' => 'text form-control', 'placeholder' => 'GPU', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('power', 'Power Supply') }}
                  {{ Form::text('power', $settings->power, array('class' => 'text form-control', 'placeholder' => 'Power Supply', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('motherboard', 'Motherboard') }}
                  {{ Form::text('motherboard', $settings->motherboard, array('class' => 'text form-control', 'placeholder' => 'Motherboard', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('computercase', 'Computer Case') }}
                  {{ Form::text('computercase', $settings->computercase, array('class' => 'text form-control', 'placeholder' => 'Computer Case', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('ram', 'RAM') }}
                  {{ Form::text('ram', $settings->ram, array('class' => 'text form-control', 'placeholder' => 'RAM', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('hd1', 'Hard Drive 1') }}
                  {{ Form::text('hd1', $settings->hd1, array('class' => 'text form-control', 'placeholder' => 'Hard Drive 1', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('hd2', 'Hard Drive 2') }}
                  {{ Form::text('hd2', $settings->hd2, array('class' => 'text form-control', 'placeholder' => 'Hard Drive 2', 'maxlength' => '70')) }}
                </div>
                <div class="form-group">
                  {{ Form::label('os', 'Operating System') }}
                  {{ Form::text('os', $settings->os, array('class' => 'text form-control', 'placeholder' => 'Operating System', 'maxlength' => '70')) }}
                </div>
                {{ Form::submit('Save', array('class' => 'submit btn btn-default')) }}
                <!-- Add recover password -->
        {{ Form::close() }}
    @endif

    </div>

@endsection
