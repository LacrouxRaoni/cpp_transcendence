import React from 'react';
import headerIcon from '../assets/header-icon1.png';

function Header(){
	return(
		<div>
			<h1 className='App-header'>
				<img className='App-header-icon' src={ headerIcon } alt="Header Icon" /> 
				PongApi 42
			</h1>
		</div>
	);
}

export default Header;