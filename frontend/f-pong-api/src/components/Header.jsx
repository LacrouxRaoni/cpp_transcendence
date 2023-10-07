import React from 'react';
import headerIcon from '../assets/header-icon1.png';

function Header(){
	return(
		<h1 className='App-header'>
			<img className='App-header-icon' src={ headerIcon } alt="Header Icon" />
			Pong API 42
		</h1>
	);
}

export default Header;